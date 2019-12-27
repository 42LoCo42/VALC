module Main where

import VALC

main :: IO ()
main = interact $ show . eval . getTerm
