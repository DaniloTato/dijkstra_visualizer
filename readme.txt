_____________________
|Dijkstra_visualizer| Read_me!!
---------------------
Made by: danilo_tato.

Compilation:
	SFML-13.1.0 lib required for compilation

	General terminal compilation commands:

			//c++17 or higher required---
		> g++ -c main.cpp -I[sfml_library_installation_path]/include -std=c++17	
		> g++ main.o -o [watever_name] -L[sfml_library_installation_path]/lib -lsfml-graphics -lsfml-window -lsfml-system
		
			//excecute the program if mac or linux
		> ./[watever_name]

			//excecute the program if windows
                > [watever_name].exe

Reelevant keys:
	[left arrow key] && [right arrow key] -> Change SELECTED NODE.
	[shift] || {right click} -> Assign SELECTED NODE the status of STARTING NODE.
	[tab] -> Delete selected node.
	[enter] -> Execute INPUT to create a new NODE.
	[backspace] -> Cancel creation of new PATH.

	{general numeric and letter keyboard keys} -> INPUT for NODE creation.
	{click} -> Create a new PATH linked to a NODE. Click again to assign said PATH to its destination node.
	{click and drag} while not clicking a node -> Move camera.
	{mouse wheel} -> Adjust camera zoom.

New node creation format:

	[x_coordinates] (space) [y_coordinates] (space) (*optional)[node name]

Terminology:
	PATH: Line with direction that connects nodes. May the pink ones be the only ones relevat to find the most optimal path to a node.
	NODE: Circle representing the intersection of paths.
	SELECTED NODE: Individual NODE covered by a yellow circle.
	STARTING NODE: Pink NODE from which the dijkstra's algorithm will start its execution.
	INPUT: String of text shown in the bottom left corner destined for the creation of new NODES.
	
