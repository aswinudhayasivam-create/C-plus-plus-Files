#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

// ---------------- NODE ----------------
struct Node {
    int id;
    QPoint pos;
};

// ---------------- PACKET ----------------
struct Packet {
    vector<int> path;
    int currentIndex = 0;
    double progress = 0.0;
};

// ---------------- NETWORK WIDGET ----------------
class NetworkWidget : public QWidget {
    vector<Node> nodes;
    vector<vector<pair<int,double>>> adj;
    vector<Packet> packets;

    QTimer timer;

public:
    NetworkWidget() {
        setFixedSize(600, 500);

        // Create nodes (fixed positions)
        nodes = {
            {0, {100,100}},
            {1, {250,50}},
            {2, {400,100}},
            {3, {150,300}},
            {4, {350,300}},
            {5, {500,200}}
        };

        adj.resize(6);
        addEdge(0,1,1);
        addEdge(1,2,1);
        addEdge(0,3,2);
        addEdge(3,4,1);
        addEdge(2,4,2);
        addEdge(4,5,1);

        connect(&timer, &QTimer::timeout, this, &NetworkWidget::updateSimulation);
        timer.start(30);
    }

    void addEdge(int u, int v, double w) {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    // DIJKSTRA
    vector<int> shortestPath(int src, int dest) {
        int n = nodes.size();
        vector<double> dist(n, 1e9);
        vector<int> parent(n, -1);

        priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d,u] = pq.top(); pq.pop();

            for (auto &edge : adj[u]) {
                int v = edge.first;
                double w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        vector<int> path;
        for (int at = dest; at != -1; at = parent[at])
            path.push_back(at);

        reverse(path.begin(), path.end());
        return path;
    }

    void sendPacket(int src, int dest) {
        Packet p;
        p.path = shortestPath(src, dest);
        packets.push_back(p);
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw edges
        painter.setPen(QPen(Qt::black, 2));
        for (int i = 0; i < adj.size(); i++) {
            for (auto &e : adj[i]) {
                painter.drawLine(nodes[i].pos, nodes[e.first].pos);
            }
        }

        // Draw nodes
        painter.setBrush(Qt::blue);
        for (auto &n : nodes) {
            painter.drawEllipse(n.pos, 15, 15);
            painter.drawText(n.pos + QPoint(-5,5), QString::number(n.id));
        }

        // Draw packets
        painter.setBrush(Qt::red);
        for (auto &p : packets) {
            if (p.currentIndex >= p.path.size()-1) continue;

            QPoint a = nodes[p.path[p.currentIndex]].pos;
            QPoint b = nodes[p.path[p.currentIndex+1]].pos;

            int x = a.x() + (b.x() - a.x()) * p.progress;
            int y = a.y() + (b.y() - a.y()) * p.progress;

            painter.drawEllipse(QPoint(x,y), 6, 6);
        }
    }

private:
    void updateSimulation() {
        for (auto &p : packets) {
            p.progress += 0.02;

            if (p.progress >= 1.0) {
                p.progress = 0;
                p.currentIndex++;

                if (p.currentIndex >= p.path.size()-1) {
                    p.currentIndex = p.path.size()-1;
                }
            }
        }

        update();
    }
};

// ---------------- MAIN ----------------
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NetworkWidget w;
    w.show();

    // Send test packets
    QTimer::singleShot(1000, [&w]() {
        w.sendPacket(0,5);
        w.sendPacket(1,5);
        w.sendPacket(2,5);
    });

    return app.exec();
}