# VALC
Variable-agnostic Lambda Calculus

## What?
It's [Lambda Calculus](https://en.wikipedia.org/wiki/Lambda_calculus), except variables are indices (starting from 0).
Also, the Lambda symbol is a `!`.

Example: the reduction of a NAND gate applied to TRUE and FALSE
```
!!(1 (0 !!0 !!1) !!1) !!1 !!0
!(!!1 (0 !!0 !!1) !!1) !!0
!!1 (!!0 !!0 !!1) !!1
!(!!0 !!0 !!1) !!1
!!0 !!0 !!1
!0 !!1
!!1
```
which is TRUE.

## Pictures
The above example

![NAND steps](https://github.com/42LoCo42/VALC/blob/master/nand-steps.png)

All four possible inputs

![NAND full](https://github.com/42LoCo42/VALC/blob/master/nand-full.png)

## Why?
Because I didn't realize that [De Brujin indexing](https://en.wikipedia.org/wiki/De_Bruijn_index) already exists.
And also because Haskell is fun.

## Credits
`Parser.hs` and my Haskell skills were ~~stolen~~ borrowed from [Tsoding](https://www.youtube.com/watch?v=N9RUqGYuGfw).
