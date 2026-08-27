#include <bits/stdc++.h>
using namespace std;

class Packet {
public:
    int id;
    int source;
    int destination;
    string data;
    double size;

    Packet(int i, int s, int d, string dat) 
        : id(i), source(s), destination(d), data(dat), size(512.0) {}

    void display() const {
        cout << "[+] Packet " << id << " created: " << data << endl;
    }
};

class Node {
public:
    int id;
    string name;
    Node(int i, string n = "") : id(i), name(n) {}
};

class Network {
private:
    vector<Node> nodes;
    vector<vector<pair<int, double>>> adj;
    int packetCounter = 0;

public:
    Network() {}

    void addNode(string name = "") {
        int id = nodes.size();
        nodes.emplace_back(id, name.empty() ? "Node" + to_string(id) : name);
        adj.emplace_back();
        cout << "[+] Node " << id << " (" << nodes[id].name << ") added successfully.\n";
    }

    void addConnection(int u, int v, double delay) {
        if (u < 0 || u >= (int)nodes.size() || v < 0 || v >= (int)nodes.size() || u == v || delay <= 0) {
            cout << "[!] Invalid connection parameters!\n";
            return;
        }
        adj[u].emplace_back(v, delay);
        adj[v].emplace_back(u, delay);
        cout << "[+] Connection added: " << u << " <-> " << v 
             << " (delay = " << delay << "s)\n";
    }

    vector<int> findShortestPath(int src, int dest) {
        if (src == dest) return {src};
        
        vector<int> parent(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (auto& p : adj[curr]) {
                int nei = p.first;
                if (!visited[nei]) {
                    visited[nei] = true;
                    parent[nei] = curr;
                    q.push(nei);
                    if (nei == dest) goto reconstruct;
                }
            }
        }

    reconstruct:
        vector<int> path;
        if (parent[dest] == -1 && src != dest) return path;

        for (int at = dest; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void sendPacket(int src, int dest, string data) {
        int pid = packetCounter++;
        Packet pkt(pid, src, dest, data);
        pkt.display();

        vector<int> path = findShortestPath(src, dest);
        if (path.empty()) {
            cout << "[!] No path exists from Node " << src << " to Node " << dest << "!\n\n";
            return;
        }

        cout << "Path taken: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;

        double currentTime = 0.0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int from = path[i];
            int to = path[i + 1];

            double delay = 0.0;
            for (auto& p : adj[from]) {
                if (p.first == to) {
                    delay = p.second;
                    break;
                }
            }

            currentTime += delay;
            cout << "   Time " << fixed << setprecision(1) 
                 << currentTime << "s: Packet moved from Node " << from 
                 << " -> Node " << to 
                 << " (delay: " << delay << "s)\n";
        }

        cout << "[+] Packet " << pid << " successfully delivered to Node " 
             << dest << " at time " << currentTime << "s!\n\n";
    }

    void displayNetwork() const {
        cout << "\n";
        cout << "==========================================================\n";
        cout << "                NETWORK TOPOLOGY (" << nodes.size() << " nodes)\n";
        cout << "==========================================================\n";

        for (int i = 0; i < (int)nodes.size(); ++i) {
            cout << "Node " << setw(2) << i << " (" << nodes[i].name << ") -> ";
            if (adj[i].empty()) {
                cout << "no connections";
            } else {
                for (auto& p : adj[i]) {
                    cout << p.first << "(d=" << p.second << "s) ";
                }
            }
            cout << endl;
        }
        cout << "==========================================================\n\n";
    }
};

void printHeader() {
    cout << "\n";
    cout << "==========================================================\n";
    cout << "          NETWORK PACKET SIMULATOR (OOP C++)\n";
    cout << "==========================================================\n\n";
}

void printMenu() {
    cout << "==========================================================\n";
    cout << "                        MAIN MENU\n";
    cout << "==========================================================\n";
    cout << "  1. Add New Node\n";
    cout << "  2. Add Connection (with delay)\n";
    cout << "  3. Send Packet\n";
    cout << "  4. Display Network Topology\n";
    cout << "  5. Exit Simulator\n";
    cout << "==========================================================\n";
    cout << "Enter your choice (1-5): ";
}

int main() {
    Network net;

    printHeader();

    // Create default example network
    cout << "Creating default example network...\n";
    for (int i = 0; i < 6; ++i) net.addNode();
    net.addConnection(0, 1, 1.2);
    net.addConnection(1, 2, 0.8);
    net.addConnection(0, 3, 2.5);
    net.addConnection(3, 4, 1.5);
    net.addConnection(2, 4, 3.0);
    net.addConnection(4, 5, 1.0);
    net.addConnection(1, 5, 4.0);

    net.displayNetwork();

    int choice;
    do {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "\nEnter node name (optional, press Enter for default): ";
            cin.ignore();
            getline(cin, name);
            net.addNode(name);
        } 
        else if (choice == 2) {
            int u, v;
            double delay;
            cout << "\nEnter Node U, Node V, Delay (seconds): ";
            cin >> u >> v >> delay;
            net.addConnection(u, v, delay);
        } 
        else if (choice == 3) {
            int src, dest;
            string data;
            cout << "\nEnter Source Node ID: ";
            cin >> src;
            cout << "Enter Destination Node ID: ";
            cin >> dest;
            cout << "Enter packet message/content: ";
            cin.ignore();
            getline(cin, data);
            cout << "\n";
            net.sendPacket(src, dest, data);
        } 
        else if (choice == 4) {
            net.displayNetwork();
        } 
        else if (choice == 5) {
            cout << "\nThank you for using the Network Packet Simulator!\n";
            cout << "Goodbye!\n\n";
        } 
        else {
            cout << "\n[!] Invalid choice! Please enter a number between 1 and 5.\n";
        }

        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (choice != 5);

    return 0;
}