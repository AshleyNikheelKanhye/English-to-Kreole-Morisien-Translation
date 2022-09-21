*-----------------------------------------------------------------------------------------------------------------
	This was my project in where it involved using classes and methods alongs with arrays and vectors in C++.
	We were already provided the (1000_English_B_040521.txt) and (1000_KM_B_040521.txt).
*-----------------------------------------------------------------------------------------------------------------



The project consists of 2 parts.

Part 1 : [Mapping.cpp] 
		-Given a dataset for 1000 English sentences(1000_English_B_040521.txt) for which there is 1000 Kreole sentences(1000_KM_B_040521.txt) already translated.
		-The English sentence on line 1 in the 1000_English_B_040521.txt is translated into Kreole Morisien on line 1 in the 1000_KM_B_040521.txt.
		-That is the English sentences have their Kreole Morisien equivalent at their corresponding line index in the txt file.
			
		-Mapping.cpp will read each English word in a Sentence and will mapp it with each Kreole Morisien word in it's equivalent Kreole Morisien sentence.
		-For each mapping is associated it's frequency , i.e the number of times that an English word has been mapped to this Kreole Morisien word.
		-The mappings will be saved in 4 different txt files.
			-'mapping for english.txt' stores the english words in the 1000 English sentences.
			-'mapping for km.txt' stores the Kreole Morisien words in the 1000 Kreole Morisien sentences.
			-'mapping for frequency.txt' stores the amount of time the corresponding English word has been mapped to a Kreole Morisien word.
			
			-'mapping for all.txt' is just to show  how all the three mapping files above are connected by line number.
		-After the Mapping.cpp has been executed, it will generate these 4 txt files which will be used for the translation program.


Part 2 : [Translate one English sentence.cpp] 
		-This program takes one English sentence as input and translate it to Kreole Morisien.
		-It will break the input English sentence into words and will loop through the files to find the highest frequency Kreole Morisien word associated to it.
		-It then outputs the translated sentence.
