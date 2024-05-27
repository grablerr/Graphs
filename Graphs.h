#include <iostream>
#include <queue>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <limits>

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

        void print_graph() const {
            for (const auto& pair : adjacency_list) {
                cout << "Vertex " << pair.first << " is connected to:" << endl;
                for (const auto& edge : pair.second) {
                    cout << "  (" << edge.from << ") ---[" << edge.distance << "]---> (" << edge.to << ")" << endl;
                }
            }
        }

        vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
            unordered_map<Vertex, Distance> distance;
            unordered_map<Vertex, Vertex> previous;
            priority_queue<pair<Distance, Vertex>, vector<pair<Distance, Vertex>>, greater<pair<Distance, Vertex>>> pq;

            for (const auto& pair : adjacency_list) {
                distance[pair.first] = numeric_limits<Distance>::max();
            }
            distance[from] = 0;
            pq.push({ 0, from });

            while (!pq.empty()) {
                Vertex current = pq.top().second;
                pq.pop();

                if (current == to) {
                    break;
                }

                for (const Edge& edge : adjacency_list.at(current)) {
                    Distance new_dist = distance[current] + edge.distance;
                    if (new_dist < distance[edge.to]) {
                        distance[edge.to] = new_dist;
                        previous[edge.to] = current;
                        pq.push({ new_dist, edge.to });
                    }
                }
            }

            vector<Edge> path;
            Vertex current = to;
            while (current != from) {
                if (previous.find(current) == previous.end()) {
                    return vector<Edge>();
                }
                Vertex prev = previous[current];
                for (const Edge& edge : adjacency_list.at(prev)) {
                    if (edge.to == current) {
                        path.push_back(edge);
                        break;
                    }
                }
                current = prev;
            }
            reverse(path.begin(), path.end());
            return path;
        }


        vector<Vertex> walk(const Vertex& start_vertex) const {
            vector<Vertex> visited_vertices;
            if (!has_vertex(start_vertex)) {
                return visited_vertices;
            }

            unordered_map<Vertex, bool> visited;
            queue<Vertex> vertex_queue;

            vertex_queue.push(start_vertex);
            visited[start_vertex] = true;

            while (!vertex_queue.empty()) {
                Vertex current = vertex_queue.front();
                vertex_queue.pop();
                visited_vertices.push_back(current);

                for (const Edge& edge : adjacency_list.at(current)) {
                    if (!visited[edge.to]) {
                        vertex_queue.push(edge.to);
                        visited[edge.to] = true;
                    }
                }
            }

            return visited_vertices;
        }

        Distance eccentricity(const Vertex& v) const {
            unordered_map<Vertex, Distance> distance;
            priority_queue<pair<Distance, Vertex>, vector<pair<Distance, Vertex>>, greater<pair<Distance, Vertex>>> pq;

            for (const auto& pair : adjacency_list) {
                distance[pair.first] = numeric_limits<Distance>::max();
            }
            distance[v] = 0;
            pq.push({ 0, v });

            while (!pq.empty()) {
                Vertex current = pq.top().second;
                pq.pop();

                for (const Edge& edge : adjacency_list.at(current)) {
                    Distance new_dist = distance[current] + edge.distance;
                    if (new_dist < distance[edge.to]) {
                        distance[edge.to] = new_dist;
                        pq.push({ new_dist, edge.to });
                    }
                }
            }

            Distance max_distance = 0;
            for (const auto& pair : distance) {
                if (pair.second != numeric_limits<Distance>::max()) {
                    max_distance = max(max_distance, pair.second);
                }
            }
            return max_distance;
        }

        Vertex find_optimal_warehouse() const {
            vector<Vertex> all_vertices = vertices();
            Vertex optimal_vertex;
            Distance min_eccentricity = numeric_limits<Distance>::max();

            for (const Vertex& v : all_vertices) {
                if (is_connected(v)) {
                    Distance e = eccentricity(v);
                    cout << "Eccentricity of vertex " << v << " is " << e << endl;
                    if (e < min_eccentricity) {
                        min_eccentricity = e;
                        optimal_vertex = v;
                    }
                }
            }

            return optimal_vertex;
        }

    private:
        unordered_map<Vertex, vector<Edge>> adjacency_list;

        bool is_connected(const Vertex& v) const {
            unordered_map<Vertex, bool> visited;
            queue<Vertex> q;
            q.push(v);
            visited[v] = true;

            while (!q.empty()) {
                Vertex current = q.front();
                q.pop();
                for (const Edge& edge : adjacency_list.at(current)) {
                    if (!visited[edge.to]) {
                        visited[edge.to] = true;
                        q.push(edge.to);
                    }
                }
            }

            for (const auto& pair : adjacency_list) {
                if (!visited[pair.first]) {
                    return false;
                }
            }

            return true;
        }
    };
}