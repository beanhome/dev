#ifndef CRC32_H
#define CRC32_H

class CRC32
{
	public:
		CRC32(void);
		~CRC32(void);

		void Initialize(void);

		bool FileCRC(const char *sFileName, unsigned long *ulOutCRC) const;
		bool FileCRC(const char *sFileName, unsigned long *ulOutCRC, unsigned long ulBufferSize) const;

		unsigned long FullCRC(const unsigned char *sData, unsigned long ulDataLength) const;
		void FullCRC(const unsigned char *sData, unsigned long ulLength, unsigned long *ulOutCRC) const;

		void PartialCRC(unsigned long *ulCRC, const unsigned char *sData, unsigned long ulDataLength) const;

	private:
		unsigned long Reflect(unsigned long ulReflect, const char cChar) const;

	private:
		unsigned long ulTable[256]; // CRC lookup table array.


	public:
		static CRC32 s_oGenerator;
};


#endif // CRC32_H
