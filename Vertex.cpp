#include "Vertex.h"
Vertex::Vertex(string item, int pos) {
	label = item;
	position = pos;
}

string Vertex::get_label() {
	return label;
}

int Vertex::get_position() {
	return position;
}

void Vertex::set_position(int pos) {
	position = pos;
}