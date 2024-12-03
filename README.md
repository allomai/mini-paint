# mini-paint
This small application allows to draw, move and edit shapes interactively with the mouse. 

Options for drawing and editing can be specified among:
- shape among line, rectangle and ellipse (default = line),
- color (default = black),
- style of the stroke (default = solid),
- witdh of of the stroke (default = 5px).

One can choose between **3 interaction-modes** among:
- drawing,
- selecting,
- resizing.
by clicking on the corresponding icons in the first box of the toolbar. 
Details on each mode follow:

**DRAWING**:
Clicking on the drawing area will start the drawing. 
Hovering will change the size and orientation of the shape from the starting point that was first clicked.
The appearance of the drawing will depend on the options chosen before starting to draw.

**SELECTING**:
This mode allows to move and to change the appearance of existing shapes. All options but the shape can be changed.
Clicking on or inside the shape selects the entity to be modified. 
Once one entity is selected, clicking on different options will change its appearance.
Hovering from a selected entity will move it.

**RESIZING**:
One has to click on the tip of a line and hover to resize it.
For rectangles and ellipses, click on the border and hover.

Future improvements:
The resizing mode is not fully functionnal yet. One can only resize a shape bigger.

