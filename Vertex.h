#ifndef VERTEX_H
#define VERTEX_H
using namespace std;
#include <string>

class Vertex {
private:
	string label;
	int position;
public:
	Vertex(string item, int pos);
	void set_position(int pos);
	int get_position();
	string get_label();
};

#endif