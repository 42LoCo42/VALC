module Parser where

import Control.Applicative
import Data.Char

-- We need an explicit unwrapping function to use the Parser outside of patterns
newtype Parser a = Parser {
  runParser :: String -> Maybe (String, a)
}

-- Level 1 Penetration
instance Functor Parser where
  fmap f (Parser p) = Parser $ \input -> do
    (input', x) <- p input
    Just (input', f x)

-- Level 2 Penetration & Chaining (for sequential parsing)
instance Applicative Parser where
  pure x = Parser $ \input -> Just (input, x)
  (Parser p1) <*> (Parser p2) = Parser $ \input -> do
    (input', f)  <- p1 input
    (input'', x) <- p2 input'
    Just (input'', f x)

-- Boolean decisions
instance Alternative Parser where
  empty = Parser $ \_ -> Nothing
  (Parser p1) <|> (Parser p2) = Parser $ \input ->
    p1 input <|> p2 input

-- Constructs a parser for a single char
charP :: Char -> Parser Char
charP c = Parser f where
  f []          = Nothing
  f (x:xs)
    | c == x    = Just (xs, c)
    | otherwise = Nothing

-- Uses chaining to parse a string
stringP :: String -> Parser String
stringP s = sequenceA $ map charP s

-- Parses a range of consecutive elements based on a predicate
spanP :: (Char -> Bool) -> Parser String
spanP f = Parser $ \input -> do
  let (token, rest) = span f input
  if null token
    then Nothing
    else Just (rest, token)

-- Number parser
numsP :: Parser Integer
numsP = read <$> spanP isDigit

-- Whitespace parser
ws :: Parser String
ws = spanP isSpace

-- Creates a parser that fails if the original one returns nothing
notNull :: Parser [a] -> Parser [a]
notNull (Parser p) = Parser $ \input -> do
  (input', xs) <- p input
  if null xs
    then Nothing
    else Just (input', xs)

-- A Parser to separate elements from eachother
sepBy :: Parser a -> Parser b -> Parser [b]
sepBy sep elem = (:) <$> elem <*> many (sep *> elem) <|> pure []

-- A Parser that parses multiple or no elements
multOrNone :: Parser a -> Parser [a]
multOrNone p = many p <|> pure []
