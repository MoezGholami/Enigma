CmpOpt		=	-O3 -Wall
CmpObjOpt	=	$(CmpOpt) -c
TestAES_Write: Test_AES_Write.out
	./Test_AES_Write.out

TestAES_Read: Test_AES_Read.out
	./Test_AES_Read.out

Test_AES_Write.out: Test_AES_Write.o AES.o Coder.o Encoder.o Decoder.o Hint_Functions.o File_Functions.o Key.o UtilityFunctions.o Exception.o
	g++ $(CmpOpt) Test_AES_Write.o AES.o Coder.o Encoder.o Decoder.o Hint_Functions.o File_Functions.o Key.o UtilityFunctions.o Exception.o -o Test_AES_Write.out

Test_AES_Read.out: Test_AES_Read.o AES.o Coder.o Encoder.o Decoder.o Hint_Functions.o File_Functions.o Key.o UtilityFunctions.o Exception.o
	g++ $(CmpOpt) Test_AES_Read.o AES.o Coder.o Encoder.o Decoder.o Hint_Functions.o File_Functions.o Key.o UtilityFunctions.o Exception.o -o Test_AES_Read.out

Test_AES_Write.o: Test_AES_Write.cpp Hint_Functions.h File_Functions.h Exception.h Coder.h Decoder.h AES.h
	g++ $(CmpObjOpt) Test_AES_Write.cpp -o Test_AES_Write.o

Test_AES_Read.o: Test_AES_Read.cpp Hint_Functions.h File_Functions.h Exception.h Coder.h Decoder.h AES.h
	g++ $(CmpObjOpt) Test_AES_Read.cpp -o Test_AES_Read.o

AES.o: AES.cpp AES.h Encoder.h Decoder.h Coding_Algorithms.h UnitsAndBasicTypes.h
	g++ $(CmpObjOpt) AES.cpp -o AES.o

Coder.o: Coder.cpp Coder.h UnitsAndBasicTypes.h File_Functions.h Key.h UtilityFunctions.h Exception.h
	g++ $(CmpObjOpt) Coder.cpp -o Coder.o

Encoder.o: Encoder.cpp Encoder.h Coder.h UnitsAndBasicTypes.h File_Functions.h
	g++ $(CmpObjOpt) Encoder.cpp -o Encoder.o

Decoder.o: Decoder.cpp Decoder.h Coder.h UnitsAndBasicTypes.h UtilityFunctions.h File_Functions.h
	g++ $(CmpObjOpt) Decoder.cpp -o Decoder.o

Hint_Functions.o: Hint_Functions.cpp Hint_Functions.h UnitsAndBasicTypes.h File_Functions.h Exception.h
	g++ $(CmpObjOpt) Hint_Functions.cpp -o Hint_Functions.o

File_Functions.o: File_Functions.cpp File_Functions.h UnitsAndBasicTypes.h Exception.h
	g++ $(CmpObjOpt) File_Functions.cpp -o File_Functions.o

Key.o: Key.cpp Key.h UnitsAndBasicTypes.h UtilityFunctions.h Exception.h File_Functions.h
	g++ $(CmpObjOpt) Key.cpp -o Key.o

UtilityFunctions.o: UtilityFunctions.cpp UtilityFunctions.h UnitsAndBasicTypes.h
	g++ $(CmpObjOpt) UtilityFunctions.cpp -o UtilityFunctions.o

Exception.o: Exception.cpp Exception.h
	g++ $(CmpObjOpt) Exception.cpp -o Exception.o

Clean:
	rm *.o *.out *.Enigma *_*.zip & reset

Experiment: Test.cpp
	g++ -Wall -g Test.cpp -o Test.out && ./Test.out
