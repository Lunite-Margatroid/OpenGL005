#pragma once

namespace LM
{
	class VertexArray
	{
	private:
		unsigned int m_VAO;	// Vertex Array Object
		unsigned int m_EBO;	// Element Buffer Object
		unsigned int m_VBO;	// Vertex Buffer Object
		int m_vertexCount;	// ������Ŀ ��������Ŀ
		std::vector<int> m_attribLayout;	// ÿ�����Ե�ά����Ŀ

		/// <summary>
	/// �������
	/// </summary>
	/// <param name="index">��������</param>
	/// <param name="nDimen">����ά��</param>
	/// <param name="stride">����</param>
	/// <param name="offset">ƫ��</param>
		void AddVertexAttrib(unsigned int index, int nDimen, int stride, int offset);

	public:
		VertexArray(int count);
		~VertexArray();
		/// <summary>
		/// ��Ӷ���
		/// </summary>
		/// <param name="count">�������</param>
		/// <param name="nDimen">ÿ����������Ե�ά��</param>
		/// <param name="data">����ָ��</param>
		void AddBuffer(int count, int nDimen, const float* data);
		void AddElementBuffer(int count, const unsigned int* data);


		void DrawElement();
		void Bind();
		void Unbind();

		void PushAttrib(int nDimen);
		void ClearAttrib();

		// Ӧ�õ�ǰ���Բ���
		void ApplyLayout();
	};
}