-- Name: Junda An
-- April 21th

import Data.List
import System.IO

knightPlace :: [Int] -> [[Int]]

knightPlace input
   | length input == 0 = []
   | otherwise = knightPlaces
   where { knightPlaces = add0 knightPlaceWithout0 knightPlaceWithout0 0;
          knightPlaceWithout0 = coorToList legalCoors listofEmptyLists;
          legalCoors = legal illegalCoors boardLength;
          illegalCoors = illegal queenCoors boardLength;
          queenCoors = listToCoor input 1;
          boardLength = length input;
          listofEmptyLists = makeEmptySublist [] boardLength
           }

-- convert list to tuples that represents the coordinates of queens
listToCoor :: [Int] -> Int -> [(Int, Int)]
listToCoor [] index = []
listToCoor (x:xs) index
   | x==0 = listToCoor xs (index+1)
   | otherwise = (index, x): listToCoor xs (index+1)

-- convert tuples to list that represents all possible coordinates of knights
coorToList :: [(Int, Int)] -> [[Int]] -> [[Int]]
coorToList [] list = list
coorToList (y:ys) list = coorToList ys (coorToIndex (fst y-1)((list !! (fst y-1)) ++ [snd y]) list)

-- convert [(x,y)] to [[...][...][y]]
coorToIndex :: Int -> n -> [n] -> [n]
coorToIndex n i list = m ++ (i:l) where (m, (_:l)) = splitAt n list

-- add 0 to empty lists
add0 ::[[Int]] -> [[Int]] -> Int -> [[Int]]
add0 [] list index = list
add0 (x:xs) list index = if length x > 0
   then add0 xs list (index+1)
   else add0 xs (coorToIndex index (0:x) list) (index+1)

-- determine the illegal positions of knight. It cannot be placed at the same vertical or horizontal line with queens.
-- it cannot be placed at the same diagonal with queens
-- it cannot be placed at the position at which it can capture queens
illegal :: [(Int, Int)] -> Int -> [(Int, Int)]
illegal queenCoors length = nub( combo (
   map (queenDiagonal length) queenCoors ++
   map (queenHorVer length) queenCoors ++
   map (knightMoves length) queenCoors))

queenDiagonal :: Int -> (Int, Int) -> [(Int, Int)]
queenDiagonal length (x,y) = [(x+a, y+b) | a <- [(-length) .. length], b <- [(-length) .. length], abs a == abs b, x+a > 0, x+a <= length, y+b > 0, y+b <= length]

queenHorVer :: Int -> (Int, Int) -> [(Int, Int)]
queenHorVer length (x,y) = [(x + a, y + b) | a <- [(-length) .. length], b <- [(-length) .. length], a == 0 || b == 0, x+a > 0, x+a <= length, y+b > 0, y+b <= length]

knightMoves :: Int -> (Int, Int) -> [(Int, Int)]
knightMoves length (x,y) = [(x+a, y+b) | a <- [-2, -1, 1, 2], b <- [-2, -1, 1, 2], abs a /= abs b, x+a > 0, x+a <= length, y+b > 0, y+b <= length]

-- combine all lists together to form a larger list
combo :: [[t]] -> [t]
combo [] = []
combo (x:xs) = x ++ combo xs

-- determine the legal positions of knight, which is the complement of illegal positions
legal :: [(Int, Int)] -> Int -> [(Int, Int)]
legal illegalCoors length = [(x,y) | x <- [1 .. length], y <- [1 .. length], (x,y) `notElem` illegalCoors]

-- make a list of zero lists
makeEmptySublist :: [[Int]] -> Int -> [[Int]]
makeEmptySublist x length = if length > 0 then makeEmptySublist ([]:x) (length-1) else x
