#include <bits/stdc++.h>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;

// ---------------- PACKET ----------------
class Packet {
public:
    int id, source, destination, priority;
    string data;
    double size;

    Packet(int i, int s, int d, string dat, int p = 1)
        : id(i), source(s), destination(d), data(dat), priority(p), size(512.0) {}

    void display() const {
        cout << "[Packet " << id << "] " << data << " (Priority: " << priority << ")\n";
    }
};

// Comparator for priority queue
struct ComparePacket {
    bool operator()(Packet a, Packet b) {
        return a.priority < b.priority;
    }
};

// ---------------- NODE ----------------
class Node {
public:
    int id;
    string name;
    bool active;

    Node(int i = 0, string n = "") : id(i), name(n), active(true) {}
};

// ---------------- NETWORK ----------------
class Network {
private:
    vector<Node> nodes;

    // adj[node] = {neighbor, {delay, bandwidth, load}}
    vector<vector<pair<int, tuple<double, int, int>>>> adj;

    int packetCounter = 0;

    // stats
    int totalPackets = 0;
    int delivered = 0;
    int dropped = 0;
    double totalDelay = 0;

public:
    void addNode(string name = "") {
        int id = nodes.size();
        nodes.emplace_back(id, name.empty() ? "Node" + to_string(id) : name);
        adj.emplace_back();
    }

    void addConnection(int u, int v, double delay, int bandwidth) {
        adj[u].push_back({v, {delay, bandwidth, 0}});
        adj[v].push_back({u, {delay, bandwidth, 0}});
    }

    // DIJKSTRA (weighted routing)
    vector<int> shortestPath(int src, int dest) {
        int n = nodes.size();
        vector<double> dist(n, 1e9);
        vector<int> parent(n, -1);
        priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();

            for (auto &edge : adj[u]) {
                int v = edge.first;
                double delay = get<0>(edge.second);

                if (!nodes[v].active) continue;

                if (dist[u] + delay < dist[v]) {
                    dist[v] = dist[u] + delay;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        vector<int> path;
        if (dist[dest] == 1e9) return path;

        for (int at = dest; at != -1; at = parent[at])
            path.push_back(at);

        reverse(path.begin(), path.end());
        return path;
    }

    bool transmit(Packet p) {
        int retries = 3;

        while (retries--) {
            vector<int> path = shortestPath(p.source, p.destination);
            if (path.empty()) {
                lock_guard<mutex> lock(mtx);
                cout << "No path for packet " << p.id << endl;
                dropped++;
                return false;
            }

            double currentTime = 0;

            for (int i = 0; i < path.size() - 1; i++) {
                int u = path[i];
                int v = path[i+1];

                for (auto &edge : adj[u]) {
                    if (edge.first == v) {
                        auto &[delay, bandwidth, load] = edge.second;

                        // congestion
                        if (load >= bandwidth) {
                            delay *= 2;
                        }

                        // packet loss
                        if (rand() % 10 == 0) {
                            lock_guard<mutex> lock(mtx);
                            cout << "Packet " << p.id << " lost, retrying...\n";
                            goto retry;
                        }

                        load++;
                        this_thread::sleep_for(chrono::milliseconds(int(delay * 500)));
                        currentTime += delay;
                        load--;
                    }
                }
            }

            {
                lock_guard<mutex> lock(mtx);
                cout << "Packet " << p.id << " delivered in " << currentTime << "s\n";
            }

            delivered++;
            totalDelay += currentTime;
            return true;

        retry:
            continue;
        }

        dropped++;
        return false;
    }

    void sendPackets(priority_queue<Packet, vector<Packet>, ComparePacket> &pq) {
        vector<thread> threads;

        while (!pq.empty()) {
            Packet p = pq.top(); pq.pop();
            totalPackets++;

            threads.emplace_back(&Network::transmit, this, p);
        }

        for (auto &t : threads) t.join();
    }

    void disableNode(int id) {
        nodes[id].active = false;
    }

    void enableNode(int id) {
        nodes[id].active = true;
    }

    void showStats() {
        cout << "\n----- NETWORK STATS -----\n";
        cout << "Total: " << totalPackets << endl;
        cout << "Delivered: " << delivered << endl;
        cout << "Dropped: " << dropped << endl;
        if (delivered)
            cout << "Avg Delay: " << totalDelay / delivered << endl;
    }

    void save(string file) {
        ofstream out(file);
        out << nodes.size() << endl;
        for (auto &n : nodes) out << n.name << endl;
    }

    void load(string file) {
        ifstream in(file);
        int n; in >> n;
        nodes.clear(); adj.clear();
        for (int i = 0; i < n; i++) {
            string name;
            in >> name;
            addNode(name);
        }
    }
};

// ---------------- MAIN ----------------
int main() {
    srand(time(0));

    Network net;

    for (int i = 0; i < 6; i++)
        net.addNode();

    net.addConnection(0,1,1.0,2);
    net.addConnection(1,2,1.5,2);
    net.addConnection(0,3,2.0,1);
    net.addConnection(3,4,1.0,1);
    net.addConnection(2,4,2.5,2);
    net.addConnection(4,5,1.0,2);

    priority_queue<Packet, vector<Packet>, ComparePacket> pq;

    pq.push(Packet(1,0,5,"Hello",2));
    pq.push(Packet(2,1,5,"Data",1));
    pq.push(Packet(3,2,5,"Video",3));

    net.disableNode(3); // simulate failure

    net.sendPackets(pq);

    net.showStats();

    net.save("network.txt");

    return 0;
}