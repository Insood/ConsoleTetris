#pragma once

template<typename T>
class Matrix
{
	int mX;
	int mY;
	std::vector< std::vector<T> > TheMatrix;

	void FillMatrix()
	{
		std::vector<T> temp(mY);
		for(int i = 0; i < mX; ++i)
		{
			TheMatrix.push_back(temp);
		}
	}
public:
	Matrix(int X, int Y)
	{
		if( (X < 1) || ( Y < 1) )
			throw std::runtime_error("Matrix::Matrix : Matrix size is illogical");
		mX = X;
		mY = Y;

		FillMatrix();
	}
	~Matrix()
	{
		
	}
	const T & GetData(int x, int y) const
	{
		if( (x > mX) || ( y > mY) || (x < 0) || (y < 0) )
			throw std::range_error("Matrix::GetData : Out of bounds");

		return TheMatrix.at(x).at(y);
	}

	void SetData(int x, int y, const T & data)
	{
		if( (x > mX) || ( y > mY) || (x < 0) || (y < 0) )
			throw std::range_error("Matrix::GetData : Out of bounds");

		TheMatrix.at(x).at(y) = data;
	}

	void Clear()
	{
		TheMatrix.clear();
		FillMatrix();
	}

	inline int GetX() const { return mX; }
	inline int GetY() const { return mY; }
};
