#ifndef DATAUND_H_INCLUDED
#define DATAUND_H_INCLUDED

class Data1D
{
	private:
		float Val;
		int Eff;
	public:
		Data1D();
		Data1D(const float, const int);
		Data1D(const Data1D&);
		~Data1D();

		/*SETTER*/
		void setVal(const float);
		void setEff(const int);

		/*GETTER*/
		float getVal() const;
		int getEff() const;
		void Affiche();

		friend std::ostream &operator<<(std::ostream &flux, Data1D const& CD1);
		Data1D& operator=(Data1D const&);
		bool operator==(Data1D const&);
		bool operator!=(Data1D const&);
};

#endif //DATAUND_H_INCLUDED
