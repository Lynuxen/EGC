Dimovski Kirjan 332CB

Bow: 2 meshes (string and arc)
Arrow: 2 meshes (triangle(tip) and the body)
Balloons: 2 meshes (string and body)
Shuriken: 1 mesh

The shurikens and balloons are the same object in memory, just rendered
at different positions saved in a struct. When the arrow is launched, the angle
of the bow is fixed and it will only move when the arrow is no longer on the
screen, the same way the obsticles are rendered. W and S work for the bow.