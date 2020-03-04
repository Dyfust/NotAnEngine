class Uniform
{
public:
	const static int nameBufferSize = 32;
private:
	char _name[Uniform::nameBufferSize]{0};
	unsigned int _type;
	void* _value;

	friend class Shader;
	friend class Material;
};