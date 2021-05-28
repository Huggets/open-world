# Syntax
an integer: a integer number
a string: a string without double or single quotes
a boolean: true or false

## Tile definition
*
StartTiles

id: ressource [isvoid]
[...]

EndTiles
*

- id is an integer which is used in the WorldPiece definition
- resource is the name of the png located in data/images/. It is the
  image the tile uses.
- isvoid is an optional boolean which indicates whether the tile must
  be considered as a void tile or not. Set to false if not indicate.

## WorldPiece definition
*
StartWorldPiece
idmatrix
EndWorldPiece

[NewWorldPieceLine]

[...]
*

The couple StartWorldPiece and EndWorldPiece defines a single piece
of world.
Each times a couple is defined, it adds it to the right of the
previous defined.

WorldPieceLine make a new empty line of pieces of world
