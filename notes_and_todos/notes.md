How to do yaml saving:

- Could do it based on which charge number it is and what days it has been charged and how much it got charged to that day. Would have entries for multiple days for charge numbers
- Could do it based on which day it is and what numbers have been charged and all other stuff inside of the specific numbers

Pros of charge number
- Could query by effort name, making it super easy to grab based off of program
- Won't have to worry about extra data stuff, as it will be under the number
Cons of charge number
- Will have to do it based on charge number, which means that eventually it will be a lot of files to load up on start up (even if it does end up in some kind of database for later querying)

Pros of date
- Will be able to get stuff based on the day, which means everything will always be in one file
Cons of date
- Will have to make extra logic to look for specific charge numbers, since the easy querying stuff will be by day rather than number

Seems like I use my sutff in a way that makes doing things by charge number a lot better and easier for now, so will go with that method and continue on for later

Note to self: Need to look into using llvm as a linker at some point and figure out how that works (probably easy enough, but still needs to be looked at and done at some point)