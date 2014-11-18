class CStaticTest
{
public:
	static CStaticTest* GetInstance()
	{
		static CStaticTest* pInstance = new CStaticTest();
		return pInstance;
	}
	void Play()
	{

	}
};