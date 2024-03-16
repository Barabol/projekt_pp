build:
	gcc src/main.c src/constants.h src/lists.h src/questionList.h src/questionList.c src/lists.c src/fileread.c src/fileread.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio
run:
	./milionerzy
clean:
	rm ./milionerzy
	gcc src/main.c src/constants.h src/lists.h src/questionList.h src/questionList.c src/lists.c src/fileread.c src/fileread.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio

