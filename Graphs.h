#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

using namespace std;

namespace graphs {
    template<typename Vertex, typename Distance = double>
    class Graph {
    public:
        struct Edge {
            Vertex from;
            Vertex to;
            Distance distance;

            Edge(const Vertex& f, const Vertex& t, const Distance& d)
                : from(f), to(t), distance(d) {}
        };

        bool has_vertex(const Vertex& v) const {
            return (adjacency_list.find(v) != adjacency_list.end());
        }

        void add_vertex(const Vertex& v) {
            if (!has_vertex(v)) {
                adjacency_list[v] = vector<Edge>();
            }
        }

        bool remove_vertex(const Vertex& v) {
            auto it = adjacency_list.find(v);
            if (it != adjacency_list.end()) {
                adjacency_list.erase(it);
                for (auto& pair : adjacency_list) {
                    auto& edges = pair.second;
                    edges.erase(remove_if(edges.begin(), edges.end(),
                        [&v](const Edge& edge) {
                            return edge.to == v || edge.from == v;
                        }),
                        edges.end());
                }
                return true;
            }
            return false;
        }

        vector<Vertex> vertices() const {
            vector<Vertex> result;
            for (const auto& pair : adjacency_list) {
                result.push_back(pair.first);
            }
            return result;
        }

        void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
           //TODO
            return false;
        }

        bool remove_edge(const Vertex& from, const Vertex& to) {
            //TODO
            return false;
        }

        bool remove_edge(const Edge& e) {
            //TODO
            return false;
        }

        bool has_edge(const Vertex& from, const Vertex& to) const {
            //TODO
            return false;
        }

        bool has_edge(const Edge& e) const {
            //TODO
            return false;
        }

        vector<Edge> edges(const Vertex& vertex) {
            //TODO
            vector<Edge> patch {};
            return patch;
        }

        size_t order() const {
            //TODO
            return 0;
        }

        size_t degree(const Vertex& v) const {
            //TODO
            return 0;
        }

        vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
            //TODO
            vector<Edge> patch {};
            return patch;
        }

        vector<Vertex> walk(const Vertex& start_vertex) const {
            //TODO
            vector<Edge> patch {};
            return patch;
        }

    private:
        unordered_map<Vertex, vector<Edge>> adjacency_list;
    };
}
