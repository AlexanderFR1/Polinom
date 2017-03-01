#include <stddef.h>
using namespace std;

struct monom
{
	float alfa;
	int powersAsInt;
	monom *next;
	
	void setPows(int *powers) // на вход идёт моном и заполненный массив от нуля до двух со степенями X Y Z
	{
		int increaser = 21;
		this->powersAsInt=0;
		for (int i=0;i<=2;i++)
		{
			this->powersAsInt = this->powersAsInt+ powers[i]*increaser;
			increaser=increaser*21;
		}
	}
	void getPowers(int *powers) // на вход идёт моном и пустой массив от нуля до двух
	{
		int pows = this->powersAsInt;
		int divider = 21*3;
		for (int i=2;i>=0;i--)
		{
			powers[i]=pows/divider;
			pows = pows/divider;
			divider = divider/21;
		}
	}
};

class polinom
{
	monom *first;
public:
	polinom ()
	{
		first=NULL;
	}
	void addMonom(monom obj) //добавление монома в начало полинома
	{
		monom *temp;
		temp = new monom;
		temp->alfa = obj.alfa;
		temp->powersAsInt=obj.powersAsInt;
		temp->next=first;
		first=temp;
	}
	void delMonom (float alfaDelete, int powersAsIntDelete)
	{
		monom *cycleTemp;
		bool exist = false;
		cycleTemp = first;
		while (cycleTemp != NULL)
		{
			if ( (cycleTemp->next->alfa == alfaDelete) && (cycleTemp->next->powersAsInt == powersAsIntDelete) && (!exist) )
				exist = true;
			cycleTemp->next=cycleTemp->next->next;
			monom *forDel;
			forDel=cycleTemp;
			delete forDel;
			return;
		}
	}

	//====================== Сортировка по значениям степеней =====================================================================================


	//=== Реализация собственно сортировки =======================================================
	void sort (int *arr, int left, int right)
	{
		int tempLeft = left;
		int tempRight = right;
		int pivot = arr[ (tempLeft + tempRight) / 2];
		while (tempLeft<=tempRight)
		{
			while (arr[tempLeft]< pivot)
				tempLeft++;
			while (arr[tempRight]>pivot)
				tempRight--;
			if (tempLeft<=tempRight)
			{                          //-------------------------------------
				int tempSwap;          //-------------------------------------
				tempSwap=tempLeft;     //-------------- SWAP -----------------
				tempLeft=tempRight;    //-------------------------------------
				tempRight=tempSwap;    //-------------------------------------
			}
		}
		if (left<tempRight)
			sort(arr,left,tempRight);
		if (right>tempLeft)
			sort(arr,tempLeft,right);
	}

	//======================================================================================================
	//============= Сортировка полинома по степеням ========================================================
	//======================================================================================================

	polinom sort (polinom object)
	{
		if ( object.first==NULL)
			throw "Polinom is empty";
		int size=0; //== число мономов =======
		monom *cycleTemp;
		cycleTemp=object.first;
		while (cycleTemp->next!=NULL)
		{
			size++;
			cycleTemp=cycleTemp->next;
		}
		
		int *arrayOfPowers = new int [size]; //=== создаём массив для значений степеней в свёртке =================

		int i=0;
		cycleTemp=object.first;
		while (cycleTemp->next!=NULL)
		{
			arrayOfPowers[i]=cycleTemp->powersAsInt;
			i++;
			cycleTemp=cycleTemp->next;
		}
		sort(arrayOfPowers,0,size-1);//=== Сортируем степени и выстраиваем из них новый массив ===========================

		polinom res;
		monom *tempMonom;
		for (int j=0; j< size;j++)
		{
			tempMonom->powersAsInt=arrayOfPowers[j];
			// поиск соответствующего alfa
			monom *cycleTemp1;
			cycleTemp1=object.first;
			while (cycleTemp1->next != NULL)
			{
				if (arrayOfPowers[j] == cycleTemp1->powersAsInt)
				{
					tempMonom->alfa=cycleTemp1->alfa;
				}
				cycleTemp1=cycleTemp1->next;				
			}
			res.addMonom(*tempMonom);
			// нашли alfa и добавили соответствующий моном в результирующий полином res
		}
		return res;
	}


	//====================== Сложение и вычитание умножение ==========================================================================================================
	//====================== Применять для отсортированных полиномов ===============================================================================================

	polinom operator+ (polinom obj)
	{
		polinom res;
		monom *cycleTemp;
		monom *cycleTemp1;
		
		cycleTemp = this->first;
		cycleTemp1=obj.first;
		while ( (cycleTemp->next!= NULL) && (cycleTemp1->next != NULL) )
		{
			monom *tempMonomForRes;
			tempMonomForRes = new monom;
			if (cycleTemp->powersAsInt == cycleTemp1->powersAsInt)
			{
				tempMonomForRes->alfa == cycleTemp->alfa + cycleTemp1->alfa;
				tempMonomForRes->powersAsInt=cycleTemp->powersAsInt;
				res.addMonom(*tempMonomForRes);
			}
			else
			{
				if (cycleTemp->powersAsInt > cycleTemp1->powersAsInt)
				{
					res.addMonom(*cycleTemp1);
					res.addMonom(*cycleTemp);
				}
				else
				{
					res.addMonom(*cycleTemp);
					res.addMonom(*cycleTemp1);
				}
			}
		}
		return res;
	}

	polinom operator- (polinom obj)
	{
		polinom res;
		monom *cycleTemp;
		monom *cycleTemp1;
		
		cycleTemp = this->first;
		cycleTemp1=obj.first;
		while ( (cycleTemp->next!= NULL) && (cycleTemp1->next != NULL) )
		{
			monom *tempMonomForRes;
			tempMonomForRes = new monom;
			if (cycleTemp->powersAsInt == cycleTemp1->powersAsInt)
			{
				tempMonomForRes->alfa == cycleTemp->alfa - cycleTemp1->alfa;
				tempMonomForRes->powersAsInt=cycleTemp->powersAsInt;
				res.addMonom(*tempMonomForRes);
			}
			else
			{
				cycleTemp1->alfa=cycleTemp1->alfa*(-1);
				if (cycleTemp->powersAsInt > cycleTemp1->powersAsInt)
				{
					res.addMonom(*cycleTemp1);
					res.addMonom(*cycleTemp);
				}
				else
				{
					res.addMonom(*cycleTemp);
					res.addMonom(*cycleTemp1);
				}
			}
		}
		return res;
	}

	//=================== Умножение полиномов =========================================================

	polinom operator* (polinom obj)
	{
		polinom res;
		monom *cycleTemp;
		int sizeOfThis=0;
		cycleTemp=this->first;
		while (cycleTemp->next!=NULL)
		{
			sizeOfThis++;
			cycleTemp=cycleTemp->next;
		}

		int sizeOfObj=0;
		cycleTemp=obj.first;
		while (cycleTemp->next!=NULL)
		{
			sizeOfObj++;
			cycleTemp=cycleTemp->next;
		}
		monom *cycleForThis;
		monom * cycleForObj;
		float tempAlfa;
		int *unlockedPowersThis;
		unlockedPowersThis = new int [3];
		int *unlockedPowersObj;
		unlockedPowersObj = new int [3];
		int *powersForResultMonom;
		powersForResultMonom = new int [3];
		cycleForThis = this->first;
		cycleForObj = obj.first;
		for (int i=0;i<sizeOfThis;i++)
		{
			for (int j=0;j<sizeOfObj;j++)
			{
				tempAlfa = cycleForThis->alfa * cycleForObj->alfa;
				cycleForThis->getPowers(unlockedPowersThis);
				cycleForObj->getPowers(unlockedPowersObj);
				for (int u=0;u<=2;u++)
				{
					powersForResultMonom[u]=unlockedPowersThis[u]+unlockedPowersObj[u];
				}
				monom *resMonom;
				resMonom = new monom;
				resMonom->alfa=tempAlfa;
				resMonom->setPows(powersForResultMonom);
				res.addMonom(*resMonom);
			}
		}
	}
};