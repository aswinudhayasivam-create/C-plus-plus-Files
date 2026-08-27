#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---------------- PACKET CLASS ----------------
class Packet {
public:
    int id;
    int source;
    int destination;
    string data;

    Packet(int id, int s, int d, string data) {
        this->id = id;
        source = s;
        destination = d;
        this->data = data;
    }
};

// ---------------- NODE CLASS ----------------
class Node {
public:
    int id;
    vector<int> neighbors;

    Node(int id = 0) {
        this->id = id;
    }

    void addNeighbor(int n) {
        neighbors.push_back(n);
    }
};

// ---------------- NETWORK CLASS ----------------
class Network {
private:
    map<int, Node> nodes;

public:
    void addNode(int id) {
        nodes[id] = Node(id);
    }

    void connectNodes(int a, int b) {
        nodes[a].addNeighbor(b);
        nodes[b].addNeighbor(a);
    }

    // BFS shortest path
    vector<int> findPath(int src, int dest) {
        map<int, bool> visited;
        map<int, int> parent;
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == dest) break;

            for (int neighbor : nodes[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        // If destination not reached
        if (!visited[dest]) {
            return {};
        }

        vector<int> path;
        int crawl = dest;
        path.push_back(crawl);

        while (crawl != src) {
            crawl = parent[crawl];
            path.push_back(crawl);
        }

        reverse(path.begin(), path.end());
        return path;
    }

    // Simulate packet transfer
    void sendPacket(Packet p) {
        cout << "\n🚀 Sending Packet " << p.id 
             << " (From " << p.source 
             << " → " << p.destination << ")\n";

        vector<int> path = findPath(p.source, p.destination);

        if (path.empty()) {
            cout << "❌ No path found! Packet dropped.\n";
            return;
        }

        for (int node : path) {

            // Random packet loss (10% chance)
            int lossChance = rand() % 10;
            if (lossChance == 0) {
                cout << "💥 Packet " << p.id << " lost at Node " << node << "!\n";
                return;
            }

            cout << "📍 Packet " << p.id << " at Node " << node << endl;

            // Random delay (0.3 to 1 sec)
            int delay = 300 + rand() % 700;
            this_thread::sleep_for(chrono::milliseconds(delay));
        }

        cout << "✅ Packet " << p.id << " Delivered Successfully!\n";
    }

    // Multi-packet queue system
    void processPackets(queue<Packet> &packetQueue) {
        while (!packetQueue.empty()) {
            Packet p = packetQueue.front();
            packetQueue.pop();
            sendPacket(p);
        }
    }
};

// ---------------- MAIN ----------------
int main() {
    srand(time(0));

    Network net;

    // Create nodes
    for (int i = 1; i <= 6; i++)
        net.addNode(i);

    // Connect nodes (Graph)
    net.connectNodes(1, 2);
    net.connectNodes(1, 3);
    net.connectNodes(2, 4);
    net.connectNodes(3, 4);
    net.connectNodes(4, 5);
    net.connectNodes(5, 6);

    // Packet queue (multi-packet system)
    queue<Packet> packetQueue;

    packetQueue.push(Packet(1, 1, 6, "Hello"));
    packetQueue.push(Packet(2, 2, 5, "Data"));
    packetQueue.push(Packet(3, 3, 6, "Message"));
    packetQueue.push(Packet(4, 1, 5, "Network"));

    // Start simulation
    cout << "🌐 NETWORK PACKET SIMULATION STARTED 🌐\n";

    net.processPackets(packetQueue);

    cout << "\n🎯 Simulation Finished!\n";

    return 0;
}