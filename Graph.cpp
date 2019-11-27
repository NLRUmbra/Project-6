#include "Graph.h"
void Graph::addVertex(string label) {
	
	Vertex item(label, count);//creates a vertex with the given info
	count++;//keeps track of how many vertexs there are 
	stuff.push_back(item);//puts this vertex into the vector of vertexes
	matrix.push_back(new vector<unsigned long>());
	for (auto v : matrix) {//makes sure everything is the same size
		v->resize(count);
	}
}

void Graph::removeVertex(string label) {
	Vertex* v1 = nullptr;
	for (auto v : stuff) {
		if (v.get_label() == label) {
			v1 = &v;
			stuff.erase(stuff.begin() + v.get_position());
			count--;
		}
	}
	auto old_matrix = matrix;
	matrix = {};
	for (int b = 0; b < count; b++) {
		matrix.push_back(new vector<unsigned long>());
	}
	for (auto g : matrix) {
		g->resize(count);
	}
	for (int i = 0; i < count + 1; i++) {
		if (i == v1->get_position()) {
			continue;
		}
		for (int j = 0; j < count + 1; j++) {
			if (j == v1->get_position()) {
				continue;

			}
			if (j < v1->get_position()) {
				matrix.at(i)->at(j) = (old_matrix.at(i)->at(j));
			}
			if (j > v1->get_position())
				matrix.at(i - 1)->at(j - 1) = (old_matrix.at(i)->at(j));
		}
	}

}

void Graph::addEdge(string label_1, string label_2, unsigned long weight) {
	Vertex* v1 = nullptr;
	Vertex* v2 = nullptr;
	for (auto v : stuff) {
		if (v.get_label() == label_1) {
			v1 = &v;
		}
		if (v.get_label() == label_2) {
			v2 = &v;
		}
	}
	if (v1 != nullptr && v2 != nullptr) {//creates the edge which is bidirectional
		matrix.at(v1->get_position())->at(v2->get_position()) = weight;
		matrix.at(v2->get_position())->at(v1->get_position()) = weight;
	}
}

void Graph::removeEdge(string label_1, string label_2) {
	addEdge(label_1, label_2, 0);//the absence of an edge is when the weight is zero so if we just make it so that the edge weight between these two points is zero then the edge will be removed
}

unsigned long Graph::shortestPath(string StartLabel, string Endlabel, vector<string> &path) {
	//cout << "what" << endl;
	set<int> sptSet;
	vector<unsigned long> distance;
	distance.resize(count);
	vector<vector<string>> important_bit;//containing the path
	for (int b = 0; b < count; b++) {
		important_bit.push_back({});
	}
	Vertex* v1 = nullptr;
	Vertex* v2 = nullptr;
	for (auto v : stuff) {
		if (v.get_label() == StartLabel) {
			v1 = &v;
		}
		if (v.get_label() == Endlabel) {
			v2 = &v;
		}
	}
	for (int i = 0; i < stuff.size(); i++) {
		if (v1->get_position() == i) {
			distance.push_back(0);
		}
		distance.push_back(10000000000);
	}
	//cout << 1 << endl;
	while (sptSet.size() != count) {
		int smol = 10000000000;
		int position;
		//cout << smol << endl;
		for (int j = 0; j < distance.size(); j++) {
				if (smol > distance[j] && sptSet.find(j) == sptSet.end()) {
					smol = distance[j];
					position = j;
					//cout << position << endl;
					//cout << smol << endl;
				}
			}
		
		sptSet.emplace(position);
		vector<unsigned long> depression = *matrix.at(position);
		for (int k = 0; k < depression.size(); k++) {//going through a specific vector and checking the distance to other connected vectors
			if (depression.at(k) != 0 && depression.at(k) + smol < distance.at(k)) {
				distance.at(k) = smol + depression.at(k);


				important_bit.at(k).clear();
				for (int gg = 0; gg < important_bit.at(position).size(); gg++) {
					important_bit.at(k).push_back(important_bit.at(position).at(gg));
				}
				important_bit.at(k).push_back(stuff[k].get_label());
			}
		}
		//want to go through a specific vector inside the matrix this is determined by the position we found
		//for (int z = 0; z < matrix.at(position)->size(); z++) {

		//}
	//	for (auto v : *(matrix[position])) {
		//	if(v!= 0)
		//}
	
	}
	path.push_back(StartLabel);
	for (int life = 0; life < important_bit.at(v2->get_position()).size(); life++) {
		path.push_back(important_bit.at(v2->get_position()).at(life));
	}
	return distance.at(v2->get_position());
}
