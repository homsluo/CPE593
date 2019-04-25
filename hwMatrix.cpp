#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

class BadSize{
private:
    const char* filename;
    int lineNum;
public:
    BadSize(const char filename[], int lineNum):filename(filename), lineNum(lineNum){}
    friend std::ostream&operator <<(std::ostream& s, const BadSize b){
        return s << b.filename << ": " << b.lineNum << " size mismatch";
    }
};

class Matrix{
private:
    int rows, cols;
    double* m;
public:
    Matrix(int rows, int cols, double val):rows(rows), cols(cols), m(new double[rows*cols]){
        for(int i = 0; i < rows*cols; i++)
            m[i] = val;
    }
    Matrix(vector<double> B): rows(B.size()), cols(1), m(new double[rows*cols]){
        for(int i = 0; i < rows*cols; i++)
            m[i] = B[i];
    }

    ~Matrix(){delete [] m;}
    Matrix(const Matrix& orig):rows(orig.rows), cols(orig.cols), m(new double[rows*cols]){
        for(int i = 0; i < rows*cols; i++)
            m[i] = orig.m[i];
    }
    void operator =(const Matrix& orig){
        if(this != &orig){
            delete [] m;
            rows = orig.rows;
            cols = orig.cols;
            for(int i = 0; i < rows*cols; i++)
                m[i] = orig.m[i];
        }
    }
    double &operator()(int r, int c){
        return m[r*cols+c];
    }


    Matrix operator+(const Matrix& a){
        if(rows != a.rows || cols != a.cols)
            throw BadSize(__FILE__, __LINE__);
        Matrix temp(rows, cols, 0);
        for(int i = 0; i < rows*cols; i++)
            temp.m[i] = m[i] + a.m[i];
        return temp;
    }

    Matrix operator*(const Matrix& a){
        if(cols != a.rows)
            throw BadSize(__FILE__, __LINE__);
        Matrix temp(rows, a.cols, 0);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < a.cols; j++){
                for(int p = 0; p < cols; p++){
                    temp.m[i*a.cols+j] += m[i*cols+p] * a.m[p*a.cols+j];
                }
            }
        }
        return temp;
    }

    Matrix operator*(double d){
        Matrix temp(rows, cols, 0);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                temp.m[i*cols+j] = m[i*cols+j]*d;
            }
        }
        return temp;
    }

    bool operator ==(const Matrix& a){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(m[i*cols+j] != a.m[i*cols+j])
                    return false;
            }
        }
        return true;
    }

    static Matrix read(istream& f){
        int n;
        f >> n;
        Matrix temp(n, n, 0);
        for(int i = 0; i < n*n; i++)
            f >> temp.m[i];
        return temp;
    }

    friend ostream&operator<<(ostream& s, const Matrix& a){
        for(int i = 0; i < a.rows; i++){
            for(int j = 0; j < a.cols; j++){
                s << a.m[i*a.cols + j] << '\t';
            }
            s << '\n';
        }
        return s;
    }

    int getRows(){
        return rows;
    }

    friend void fullPivot(int i, Matrix& m, vector<double>& B, vector<int>& listx){
        int biggestPos_x = i;
        int biggestPos_y = i;
        double biggest = m(i, i);
        for(int p = i; p < m.rows; p++){
            for(int q = i; q < m.cols; q++){
                if(abs(m(p, q)) > abs(biggest)){
                    biggest = m(p, q);
                    biggestPos_x = p;
                    biggestPos_y = q;
                }
            }
        }
        if(i != biggestPos_x){
            for(int t = 0; t < m.cols; t++){
                swap(m(i, t), m(biggestPos_x, t));
            }
            swap(B[i], B[biggestPos_x]);
        }
        if(i != biggestPos_y){
            for(int t = 0; t < m.rows; t++){
                swap(m(t, i), m(t, biggestPos_y));
            }
            swap(listx[i], listx[biggestPos_y]);
        }
    }
    friend void partialPivot(int i, Matrix& m, vector<double>& B){
        int biggestPos = i;
        double biggest = m(i,i);
        for(int j = i; j < m.rows; j++){
            if(abs(m(j, i)) > abs(biggest)){
                biggest = m(j, i);
                biggestPos = j;
            }
        }
        if(i != biggestPos){
            for(int t = 0; t < m.cols; t++){
                swap(m(i, t), m(biggestPos, t));
            }
            swap(B[i], B[biggestPos]);
        }
    }

    friend void fullbackSubstitute(Matrix& m, vector<double>& x, vector<double>& B, vector<int>& listx){
        for(int n = m.rows; n > 0; n--){
            x[listx[n-1]] = B[n-1] / m(n-1, n-1);
            for(int j = n - 2; j >= 0; j--)
                B[j] -= m(j, n-1) * x[listx[n-1]];
        }
    }
    friend void partialbackSubstitute(Matrix& m, vector<double>& x, vector<double>& B){
        for(int n = m.rows; n > 0; n--){
            x[n-1] = B[n-1] / m(n-1, n-1);
            for(int j = n - 2; j >= 0; j--)
                B[j] -= m(j, n-1) * x[n-1];
        }
    }

    friend vector<double> partialsolve(Matrix m, vector<double> B){
        if(B.size() != m.rows && m.rows != m.cols)
            throw BadSize(__FILE__, __LINE__);
        vector<double> x;
        x.resize(m.rows);
        for(int i = 0; i < m.rows-1; i++){
            partialPivot(i, m, B);
//            cout << m << '\n';
            for(int k = i+1; k < m.rows; k++){
                double s = -m(k, i)/m(i, i);
                m(k, i) = 0;
                for(int j = i+1; j < m.cols; j++)
                    m(k, j) += s * m(i, j);
                B[k] += s * B[i];
//                cout << m << '\n';
            }
        }
        partialbackSubstitute(m, x, B);
        return x;
    }
    friend vector<double> fullsolve(Matrix m, vector<double> B){
        if(B.size() != m.rows && m.rows != m.cols)
            throw BadSize(__FILE__, __LINE__);
        vector<double> x;
        x.resize(m.rows);
        vector<int> listx;
        listx.resize(m.rows);
        for(int t = 0; t < listx.size(); t++){
            listx[t] = t;
        }
        for(int i = 0; i < m.rows-1; i++){
            fullPivot(i, m, B, listx);
            for(int k = i+1; k < m.rows; k++){
                double s = -m(k, i)/m(i, i);
                m(k, i) = 0;
                for(int j = i+1; j < m.cols; j++)
                    m(k, j) += s * m(i, j);
                B[k] += s * B[i];
            }
        }
        fullbackSubstitute(m, x, B, listx);
        return x;
    }

    static Matrix random(int n){
        Matrix temp(n, n, 0);
        srand(time(NULL));
        for(int i = 0; i < n*n; i++){
            temp.m[i] = rand() % 19 - 9;
        }
        return temp;
    }

    Matrix row(int r){
        Matrix temp(1, cols, 0);
        for(int i = 0; i < cols; i++)
            temp.m[i] = m[r*cols+i];
        return temp;
    }
    Matrix col(int c){
        Matrix temp(rows, 1, 0);
        for(int i = 0; i < rows; i++)
            temp.m[i] = m[i*cols+c];
        return temp;
    }

    bool cond() {
        for (int i = 0; i < cols; i++) { // 0 col
            if (m[i] == 0) {
                double sum = 0;
                for (int j = 1; j < rows; j++)
                    sum += abs(m[j * cols + i]);
                if (sum == 0)
                    return false;
            }
        }
        for (int i = 0; i < rows; i++) {   // 0 row
            if (m[i * cols] == 0) {
                double sum = 0;
                for (int j = 1; j < cols; j++)
                    sum += abs(m[i * cols + j]);
                if (sum == 0)
                    return false;
            }
        }
        for(int i = 0; i < cols; i++){
            if(m[i] != 0){
                for(int j = 1; j < rows; j++){
                    if(m[j*cols+i] != 0){
                        double d = m[i] / m[j*cols+i];
                        if(row(j)*d == row(0))
                            return false;
                    }
                }
                break;
            }
        }
        for(int i = 0; i < rows; i++){
            if(m[i*cols] != 0){
                for(int j = 1; j < cols; j++){
                    if(m[i*cols+j] != 0){
                        double d = m[i] / m[i*cols+j];
                        if(col(j)*d == col(0))
                            return false;
                    }
                }
                break;
            }
        }
        return true;
    }

    double diff(const Matrix& a){
        double sum = 0;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum += pow(m[i*cols+j] - a.m[i*cols+j], 2);
            }
        }
        return sum;
    }
};

vector<double> read(int n, istream& s) {
    vector<double> B;
    B.reserve(n);
    double tmp;
    for (int i = 0; i < n; ++i) {
        s >> tmp;
        B.push_back(tmp);
    }
    return B;
}

int main() {
    Matrix m1(3, 4, 0.0);
    m1(1,2) = 1.5;  // Java: m1.set(1,2,1.5);
    Matrix m2(3, 4, 1.0);
    Matrix m3 = m1 + m2; // matrix addition
    cout << m3 << '\n';

    Matrix m4(4, 2, 0.5);
    m4(0,0) = 5.0;
//    m4(0,2) = -1.0;
    Matrix m5 = m1 * m4;
    cout << m5 << '\n';
    ifstream f("hw5.dat");
    Matrix A = Matrix::read(f);
    cout << A << '\n';
    vector<double> B = read(A.getRows(), f);
    try{
        vector<double> x1 = fullsolve(A, B);
        cout << "Full Pivoting: " << '\t';
        for (auto v : x1) {
            cout << v << ' ';
        }
        cout << '\n';
        vector<double> x2 = partialsolve(A, B);
        cout << "Partial Pivot: " << '\t';
        for (auto v : x2) {
            cout << v << ' ';
        }
        cout << '\n';
    }catch (BadSize& a){
        cout << a << '\n';
    }
    Matrix m10 = Matrix::random(10);
    while(!m10.cond()){
        m10 = Matrix::random(10);
    }
//    cout << m10 << '\n';
    Matrix m20 = Matrix::random(20);
    while(!m20.cond()){
        m20 = Matrix::random(20);
    }

    vector<double> B10;
    vector<double> B20;
    for(int i = 0; i < 10; i++)
        B10.push_back(rand()%19-9);
    for(int i = 0; i < 20; i++)
        B20.push_back(rand()%19-9);

    try{
        vector<double>x_10F = fullsolve(m10,B10);
        vector<double>x_10P = partialsolve(m10,B10);
        vector<double>x_20F = fullsolve(m20, B20);
        vector<double>x_20P = partialsolve(m20, B20);
        Matrix r1 = m10 * Matrix(x_10F);
        Matrix r2 = m10 * Matrix(x_10P);
        Matrix r3 = m20 * Matrix(x_20F);
        Matrix r4 = m20 * Matrix(x_20P);
        cout << "Full Pivoting(10): "  << '\t' << r1.diff(Matrix(B10)) << '\n';
        cout << "Partial Pivoting(10): "  << '\t' << r2.diff(Matrix(B10)) << '\n';
        cout << "Full Pivoting(20): "  << '\t' << r3.diff(Matrix(B20)) << '\n';
        cout << "Partial Pivoting(20): "  << '\t' << r4.diff(Matrix(B20)) << '\n';
    }catch (BadSize b){
        cout << b <<'\n';
    }
}