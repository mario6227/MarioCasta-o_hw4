all: wave

wave: Plots.py Resultados_hw4.tex
	cc Ondas.c -lm -o Ondas.x
	./Ondas.x
	python Plots.py
	pdflatex Resultados_hw4.tex

Plots.py: Ondas.c
	cc Ondas.c -lm -o Ondas.x
	./Ondas.x
	python Plots.py

Resultados_hw4.tex: Plots.py
	python Plots.py
	pdflatex Resultados_hw4.tex

