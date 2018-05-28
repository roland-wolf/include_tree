# include_tree
Qt Gui Application to analyze the cost of C/C++ include statements

Fight C++ compile time by analyzing the cost of include chains! 

include_tree reads preprocessed sources and shows the most expensive headers in the project. 
Compile a gcc project with flag -save-temps to get preprocessed files. Start include_tree and press File/Load Directory... 
to load your preprocessed sources. 

include_tree simply counts the number of lines a header contributes to a project by being included several times. 
True parsing and processing cost are ignored. 

include_tree is in early state of development but proofed to be useful in real projects. 
