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
            add_vertex(from);
            add_vertex(to);
            adjacency_list[from].emplace_back(from, to, d);
        }

        bool remove_edge(const Vertex& from, const Vertex& to) {
            auto it = adjacency_list.find(from);
            if (it != adjacency_list.end()) {
                auto& edges = it->second;
                auto edge_it = remove_if(edges.begin(), edges.end(),
                    [&to](const Edge& edge) {
                        return edge.to == to;
                    });
                if (edge_it != edges.end()) {
                    edges.erase(edge_it, edges.end());
                    return true;
                }
            }
            return false;
        }

        bool remove_edge(const Edge& e) {
            auto it = adjacency_list.find(e.from);
            if (it != adjacency_list.end()) {
                auto& edges = it->second;
                auto edge_it = remove_if(edges.begin(), edges.end(),
                    [&e](const Edge& edge) {
                        return edge.to == e.to && edge.distance == e.distance;
                    });
                if (edge_it != edges.end()) {
                    edges.erase(edge_it, edges.end());
                    return true;
                }
            }
            return false;
        }

        bool has_edge(const Vertex& from, const Vertex& to) const {
            auto it = adjacency_list.find(from);
            if (it != adjacency_list.end()) {
                const auto& edges = it->second;
                return any_of(edges.begin(), edges.end(),
                    [&to](const Edge& edge) {
                        return edge.to == to;
                    });
            }
            return false;
        }

        bool has_edge(const Edge& e) const {
            auto it = adjacency_list.find(e.from);
            if (it != adjacency_list.end()) {
                const auto& edges = it->second;
                return any_of(edges.begin(), edges.end(),
                    [&e](const Edge& edge) {
                        return edge.to == e.to && edge.distance == e.distance;
                    });
            }
            return false;
        }

        vector<Edge> edges(const Vertex& vertex) {
            auto it = adjacency_list.find(vertex);
            if (it != adjacency_list.end()) {
                return it->second;
            }
            return vector<Edge>();
        }

        size_t order() const {
            return adjacency_list.size();
        }

        size_t degree(const Vertex& v) const {
            auto it = adjacency_list.find(v);
            if (it != adjacency_list.end()) {
                return it->second.size();
            }
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
