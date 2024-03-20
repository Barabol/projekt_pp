build:
	gcc src/main.c src/ratunki.c src/ratunki.h src/constants.h src/lists.h src/questionList.h src/questionList.c src/lists.c src/fileread.c src/fileread.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec

run:
	./milionerzy
clean:
	rm ./milionerzy
	gcc src/main.c  src/ratunki.c src/ratunki.h  src/constants.h src/lists.h src/questionList.h src/questionList.c src/lists.c src/fileread.c src/fileread.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec

