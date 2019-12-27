module VALC where

import Parser
import Control.Applicative
import Data.Char
import Data.Functor
import Data.Maybe

-- Parsing

optionalWs = optional ws

data VALC_Term = VALC_Chain       [VALC_Term]
               | VALC_Variable    Integer
               | VALC_Symbol      String
               | VALC_Abstraction VALC_Term

valcParser :: Parser VALC_Term
valcParser = VALC_Chain <$> valcRawChain <&> tryCollapseChain

valcRawChain :: Parser [VALC_Term]
valcRawChain = sepBy optionalWs valcTerm <&> map tryCollapseChain

valcTerm :: Parser VALC_Term
valcTerm = optionalWs *>
           valcBracketed <|>
           valcVariable  <|>
           valcSymbol    <|>
           valcAbstraction
           <* optionalWs

valcBracketed :: Parser VALC_Term
valcBracketed = VALC_Chain <$> (charP '(' *> optionalWs *>
                               valcRawChain
                               <* optionalWs <* charP ')') <&> tryCollapseChain

valcVariable :: Parser VALC_Term
valcVariable = VALC_Variable <$> numsP

valcSymbol :: Parser VALC_Term
valcSymbol = VALC_Symbol <$> spanP isLetter

valcAbstraction :: Parser VALC_Term
valcAbstraction = VALC_Abstraction <$> (charP '!' *> valcTerm)

tryCollapseChain                     :: VALC_Term -> VALC_Term
tryCollapseChain (VALC_Chain [elem]) = elem
tryCollapseChain other               = other

-- Evaluation

getTerm :: String -> VALC_Term
getTerm input = snd $ fromMaybe ("", VALC_Symbol "ERROR") $ runParser valcParser input

eval :: VALC_Term -> VALC_Term
eval (VALC_Chain (t1:t2:rest)) = tryCollapseChain $ VALC_Chain ((apply t1 t2):rest) -- if we eval the result, infinite recursion might appear
eval other = other

apply :: VALC_Term -> VALC_Term -> VALC_Term
apply (VALC_Abstraction body) t2 = replaceVar 0 t2 body
apply t1@(VALC_Chain _)       t2 = apply (eval t1) t2 -- we need the left side before applying t2 to it
apply t1                      t2 = VALC_Chain [t1, eval t2]

replaceVar :: Integer -> VALC_Term -> VALC_Term -> VALC_Term
replaceVar tval term v@(VALC_Variable val)
  | val == tval = term
  | otherwise   = v
replaceVar tval term (VALC_Chain body)       = VALC_Chain $ map (replaceVar tval term) body
replaceVar tval term (VALC_Abstraction body) = VALC_Abstraction $ replaceVar (tval+1) term body
replaceVar _    _    other                   = other

-- Show

instance Show VALC_Term where
  show (VALC_Chain body)       = "(" ++ (foldl (++) "" $ map show body) ++ ") "
  show (VALC_Variable body)    = show body ++ " "
  show (VALC_Symbol body)      = body ++ " "
  show (VALC_Abstraction body) = "!" ++ show body
