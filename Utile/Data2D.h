#ifndef Data2D_H_INCLUDED
#define Data2D_H_INCLUDED


class Data2D
{
	private:
		float Val1;
		float Val2;
	public:
		Data2D();
		Data2D(const float, const float);
		Data2D(const Data2D&);
		~Data2D();

		/*SETTER*/
		void setVal1(const float);
		void setVal2(const float);

		/*GETTER*/
		float getVal1() const;
		float getVal2() const;

		Data2D& operator=(Data2D const&);
		bool operator==(Data2D const&);
		bool operator!=(Data2D const&);
		friend std::ostream &operator<<(std::ostream &flux, Data2D const& CD2);
};

#endif //Data2D_H_INCLUDED
