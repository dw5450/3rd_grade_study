#include <python.h> 

static PyObject *

spam_CalPower(PyObject *self, PyObject *args)
{
	float ������ = 0;

	float ��or���� = 0;
	float ���ݷ� = 0;
	float ũ��Ƽ�� = 0;
	float �Ӽ���ȭ = 0;

	float ���������� = 0;
	float ���������������ݷ����� = 0;
	float ���������� = 0;
	float �߰����������� = 0;
	float ũ��Ƽ������������ = 0;
	float �߰�ũ��Ƽ������������ = 0;
	float �߰������� = 0;
	float �Ӽ��߰������� = 0;
	float �����ݷ����� = 0;
	float ��ų���ݷ����� = 0;
	

	if (!PyArg_ParseTuple(args, "ffffffffffffff",&��or����		,&���ݷ�		, &ũ��Ƽ��		,&�Ӽ���ȭ
											,&����������		, &���������������ݷ�����	, &����������
											, &�߰�����������	,&ũ��Ƽ������������		, &�߰�ũ��Ƽ������������ 
											, &�߰�������		, &�Ӽ��߰�������
											,&�����ݷ�����			, &��ų���ݷ�����)); // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.



	if (ũ��Ƽ�� > 97)
		ũ��Ƽ�� = 97;

	������ = (1 + (��or����)* (1 + ���������� / 100))/250 * (���ݷ� * (1 + ���������������ݷ����� / 100)) 
		* 1.5 * (ũ��Ƽ��/97) * (1 + (�Ӽ���ȭ +11))/222
		* (1 + ���������� / 100 + �߰����������� / 100) * (1 + ũ��Ƽ������������ / 100 + �߰�ũ��Ƽ������������ / 100)
		* (1 + �߰������� / 100 + �Ӽ��߰������� * (1.05 + 0.0045 * �Ӽ���ȭ))
		* (1 + �����ݷ����� / 100) * (1 + ��ų���ݷ����� / 100);
	

	return Py_BuildValue("f", ������);
}

static PyMethodDef SpamMethods[] = {
	{ "CalPower", spam_CalPower, METH_VARARGS,
	"calculate power.." },
	{ NULL, NULL, 0, NULL } // �迭�� ���� ��Ÿ���ϴ�.
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",            // ��� �̸�
	"calculate power.", // ��� ������ ���� �κ�, ����� __doc__�� ����˴ϴ�.
	-1,SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
	return PyModule_Create(&spammodule);
}
