module main;

import std.stdio;
import std.conv;
import std.format;
import std.array;
import std.string;
import std.algorithm;
import std.container;
import std.typecons;

import euler_lib;

enum N = 80;
enum string FILE = "p082_matrix.txt";
enum string[] TEST =   ["131, 673, 234, 103, 18",
                        "201, 96, 342, 965, 150",
                        "630, 803, 746, 422, 111",
                        "537, 699, 497, 121, 956",
                        "805, 732, 524, 37, 331"];

enum string[] MINI_TEST = ["121, 956",
                            "37, 331"];


class Matrix(ulong N)
{
    ulong[N][N]     values;

    this(string[] lines)
    {
        string[] str_values;

        foreach (n; 0 .. N)
        {
            str_values = lines[n].split(',');
            foreach (m; 0 .. N)
            {
                values[n][m] = to!ulong(strip(str_values[m]));
            }
        }
    }

    bool last_row_col(ulong row_col) const pure nothrow
    {
        return row_col == N - 1;
    }

    bool first_row_col(ulong row_col) const pure nothrow
    {
        return row_col == 0;
    }

    override string toString() const
    {
        string result;

        foreach (row; values)
        {
            result ~= format("%4s\n", row);
        }

        return result;
    }

}

class Node
{
    ulong value;
    ulong row;
    ulong col;
    Node previous;
    ulong distance;
    bool visited;

    this(ulong value, ulong row, ulong col)
    {
        this.value = value;
        this.row = row;
        this.col = col;
    }

    override int opCmp(const Object rhs) const
    {
        Node _rhs = cast(Node)rhs;

        if (this.distance == _rhs.distance)
        {
            if (this.value == _rhs.value)
                return &_rhs != cast(Node *)this;
            
            return this.value < _rhs.value ? -1 : this.value > _rhs.value;
        }

        return this.distance < _rhs.distance ? -1 : this.distance > _rhs.distance;
    }

    override bool opEquals(const Object rhs) const
    {
        Node _rhs = cast(Node)rhs;

        return this.value == _rhs.value;
    }

    override string toString() const
    {
        return format("%s", value);
    }
}

class Solver(ulong N)
{
    Node[N][N] nodes;
    RedBlackTree!Node queue;

    this(const Matrix!N matrix)
    {
        foreach (m; 0 .. N)
        {
            foreach (n; 0 .. N)
            {
                nodes[m][n] = new Node(matrix.values[m][n], m, n);
            }
        }

        queue = new RedBlackTree!Node();
    }
    
    private void _clear()
    {
        foreach (row; nodes)
        {
            foreach (n; row)
            {
                n.visited = false;
            }
        }

        queue = new RedBlackTree!Node();
    }

    private bool _last_node(const Node node) const pure
    {
        return node.col == N - 1;
    }

    private void _queue_node(ulong row, ulong col, Node previous)
    {
        if (nodes[row][col].visited)
            return ;
        
        nodes[row][col].previous = previous;
        nodes[row][col].distance = previous ?
                    previous.distance + nodes[row][col].value : nodes[row][col].value;
        queue.insert(nodes[row][col]);
    }

    private void _queue_nodes(Node node)
    {
        if (node.col == 0)
        {
            return _queue_node(node.row, node.col + 1, node);
        }

        if (node.row > 0)
            _queue_node(node.row - 1, node.col, node);
        
        if (node.col < N - 1)
            _queue_node(node.row, node.col + 1, node);
        
        if (node.row < N - 1)
            _queue_node(node.row + 1, node.col, node);
    }

    private bool _visit(Node node)
    {
        node.visited = true;
        // node.distance = node.previous ? node.previous.distance + node.value : node.value;

        if (_last_node(node))
            return true;
        
        _queue_nodes(node);

        return false;
    }

    ulong[] find_path(ulong row, ulong col)
    {
        Node current;

        _visit(nodes[row][col]);
        // writeln(queue);

        while (true)
        {
            current = queue.front();
            queue.removeFront();

            if (_visit(current))
                return get_path(current);

            // writeln(queue);
        }

        return null;
    }

    ulong[] get_path(Node node) const 
    {
        ulong[] path;

        while (node)
        {
            path = node.value ~ path;
            node = node.previous;
        }

        return path;
    }

    ulong[][] find_all_paths()
    {
        ulong[][]   paths;
        ulong[]     path;

        foreach (n; 0 .. N)
        {
            path = find_path(n, 0);
            paths ~= path;

            // writeln(path);
            
            _clear();
        }

        return paths;
    }
}

private ulong[] _min_path(ulong[][] paths...) pure
{
    ulong   min;
    ulong   current;
    long    index;

    min = ulong.max;
    foreach (n; 0 .. paths.length)
    {
        current = sum(paths[n]);
        if (current > 0 && current < min)
        {
            min = current;
            index = n;
        }
    }

    return paths[index];
}

void main()
{
    // string[] lines;
    // Matrix!N matrix;
    // Solver!N solver;

    // lines = read_file_by_line(FILE);
    // matrix = new Matrix!N(lines);
    // solver = new Solver!N(matrix);
    // ulong[] path = solver.find_path(2, 0);
    // writeln(path);
    // ulong[][] paths = solver.find_all_paths();
    // writeln(sum(_min_path(paths)));

    Matrix!5 m = new Matrix!5(TEST);
    Solver!5 solver = new Solver!5(m);
    // ulong[] path = solver.find_path(0, 0);
    ulong[][] paths = solver.find_all_paths();
    writeln(sum(_min_path(paths)));

    // ulong[][] paths = solver.find_all_paths();
    // writeln(_min_path(paths));

    // RedBlackTree!Node t = new RedBlackTree!Node();
    // t.insert(new Node(1, 0, 0));
    // t.insert(new Node(10, 0, 0));
    // writeln(t);
    // t.insert(new Node(10, 0, 0));
    // writeln(t);

    // Node x = t.front();
    // writeln(x);
}