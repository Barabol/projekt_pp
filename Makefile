build:
	gcc src/main.c src/constants.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio
run:
	./milionerzy
clean:
	rm ./milionerzy
	gcc src/main.c src/constants.h -o milionerzy -lallegro -lallegro_ttf -lallegro_font -lallegro_image -lallegro_audio

