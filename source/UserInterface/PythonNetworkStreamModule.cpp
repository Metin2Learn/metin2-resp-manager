// find:
PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	char * szLog;
	if (!PyTuple_GetString(poArgs, 0, &szLog))
		return Py_BuildException();

	return Py_BuildNone();
}

// paste below:
#ifdef ENABLE_RESP_SYSTEM
PyObject* netSendRespFetchDropPacket(PyObject* poSelf, PyObject* poArgs)
{
	uint32_t mobVnum;
	if (!PyTuple_GetUnsignedInteger(poArgs, 0, &mobVnum))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendRespFetchDropPacket(mobVnum);

	return Py_BuildNone();
}

PyObject* netSendRespFetchRespPacket(PyObject* poSelf, PyObject* poArgs)
{
	uint32_t mobVnum;
	if (!PyTuple_GetUnsignedInteger(poArgs, 0, &mobVnum))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendRespFetchRespPacket(mobVnum);

	return Py_BuildNone();
}

PyObject* netSendRespTeleportPacket(PyObject* poSelf, PyObject* poArgs)
{
	size_t id;
	if (!PyTuple_GetUnsignedInteger(poArgs, 0, &id))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendRespTeleportPacket(id);

	return Py_BuildNone();
}
#endif

// find:
		{ "RegisterErrorLog",						netRegisterErrorLog,						METH_VARARGS },

// paste below:
#ifdef ENABLE_RESP_SYSTEM
		{ "SendRespFetchDropPacket",		netSendRespFetchDropPacket,			METH_VARARGS },
		{ "SendRespFetchRespPacket",		netSendRespFetchRespPacket,			METH_VARARGS },
		{ "SendRespTeleportPacket",			netSendRespTeleportPacket,			METH_VARARGS },
#endif
