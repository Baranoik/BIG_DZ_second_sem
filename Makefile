Field.o: Field.cpp Field.h constans.h Obj.h Log_config.h
	g++ -c Field.cpp 

Obj.o: Obj.cpp Obj.h
	g++ -c Obj.cpp

Field_loged.o: Field.cpp Field.h constans.h Obj.h Log_config.h
	g++ -c Field.cpp -DLOGQM

Obj_loged.o: Obj.cpp Obj.h
	g++ -c Obj.cpp -DLOGQM

 test_01b.o: test_01b.cpp Field.h Obj.h 
	g++ -c test_01b.cpp -DLOGQM



test_01b: test_01b.o Field_loged.o Obj_loged.o
	g++ test_01b.o Field.o Obj.o -o test_01b




clean:
	rm -f *.o test_01b

T01b: test_01b
	./test_01b
