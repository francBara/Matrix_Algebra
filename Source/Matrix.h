class Matrix
{	

	public:
		int ** matrix;
		int rows;
		int columns;
		std::string name;
		int det;
		bool calcedDet = false;

	public:
		Matrix();
		Matrix(int, int);
		void init(int, int);
		void free();
		void printMatrix();
		void randomGenerate();
		void getIdentity();
		int Determinant();
		Matrix Transposed();

	private:
		int calcDeterminant(int, int *);
	
};
