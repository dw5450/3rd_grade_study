#include <python.h> 

static PyObject *

spam_CalPower(PyObject *self, PyObject *args)
{
	float 전투력 = 0;

	float 힘or지능 = 0;
	float 공격력 = 0;
	float 크리티컬 = 0;
	float 속성강화 = 0;

	float 힘지능증가 = 0;
	float 물리마법독립공격력증가 = 0;
	float 증가데미지 = 0;
	float 추가증가데미지 = 0;
	float 크리티컬증가데미지 = 0;
	float 추가크리티컬증가데미지 = 0;
	float 추가데미지 = 0;
	float 속성추가데미지 = 0;
	float 모든공격력증가 = 0;
	float 스킬공격력증가 = 0;
	

	if (!PyArg_ParseTuple(args, "ffffffffffffff",&힘or지능		,&공격력		, &크리티컬		,&속성강화
											,&힘지능증가		, &물리마법독립공격력증가	, &증가데미지
											, &추가증가데미지	,&크리티컬증가데미지		, &추가크리티컬증가데미지 
											, &추가데미지		, &속성추가데미지
											,&모든공격력증가			, &스킬공격력증가)); // 매개변수 값을 분석하고 지역변수에 할당 시킵니다.



	if (크리티컬 > 97)
		크리티컬 = 97;

	전투력 = (1 + (힘or지능)* (1 + 힘지능증가 / 100))/250 * (공격력 * (1 + 물리마법독립공격력증가 / 100)) 
		* 1.5 * (크리티컬/97) * (1 + (속성강화 +11))/222
		* (1 + 증가데미지 / 100 + 추가증가데미지 / 100) * (1 + 크리티컬증가데미지 / 100 + 추가크리티컬증가데미지 / 100)
		* (1 + 추가데미지 / 100 + 속성추가데미지 * (1.05 + 0.0045 * 속성강화))
		* (1 + 모든공격력증가 / 100) * (1 + 스킬공격력증가 / 100);
	

	return Py_BuildValue("f", 전투력);
}

static PyMethodDef SpamMethods[] = {
	{ "CalPower", spam_CalPower, METH_VARARGS,
	"calculate power.." },
	{ NULL, NULL, 0, NULL } // 배열의 끝을 나타냅니다.
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",            // 모듈 이름
	"calculate power.", // 모듈 설명을 적는 부분, 모듈의 __doc__에 저장됩니다.
	-1,SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
	return PyModule_Create(&spammodule);
}
