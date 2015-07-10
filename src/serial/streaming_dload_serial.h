/**
* LICENSE PLACEHOLDER
*
* @file streaming_dload_serial.h
* @class StreamingDloadSerial
* @package OpenPST
* @brief Streaming DLOAD protocol serial port implementation
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#ifndef _SERIAL_STREAMING_DLOAD_SERIAL_H
#define _SERIAL_STREAMING_DLOAD_SERIAL_H

#include "include/definitions.h"
#include "serial/serial.h"
#include "serial/hdlc_serial.h"
#include "util/hexdump.h"
#include "util/endian.h"
#include "qc/streaming_dload.h"
#include "qc/hdlc.h"

namespace openpst {

	enum STREAMING_DLOAD_OPERATION_RESULT {
		STREAMING_DLOAD_OPERATION_IO_ERROR = -1,
		STREAMING_DLOAD_OPERATION_ERROR = 0,
		STREAMING_DLOAD_OPERATION_SUCCESS = 1
	}; 
	
	struct streaming_dload_device_state {
		uint8_t openMode;
		uint8_t openMultiMode;
		streaming_dload_hello_rx_t hello;
		streaming_dload_error_rx_t lastError;
		streaming_dload_log_rx_t   lastLog;
	}; 
	
	class StreamingDloadSerial : public HdlcSerial {
		public:
            StreamingDloadSerial(std::string port, int baudrate = 115200);
            ~StreamingDloadSerial();

			int sendHello(std::string magic, uint8_t version, uint8_t compatibleVersion, uint8_t featureBits);
			int sendUnlock(std::string code);
			int setSecurityMode(uint8_t mode);
			int sendNop(); 
			int sendReset();
			int sendPowerOff();
			int readEcc(uint8_t& statusOut);
			int setEcc(uint8_t status);
			int openMode(uint8_t mode);
			int closeMode();
			int openMultiImage(uint8_t imageType);
			int readAddress(uint32_t address, size_t length, uint8_t** out, size_t& outSize);
			int readAddress(uint32_t address, size_t length, std::vector<uint8_t> &out);
			int readQfprom(uint32_t rowAddress, uint32_t addressType);
			int writePartitionTable(std::string filePath, uint8_t& outStatus, bool overwrite = false);

			streaming_dload_hello_rx_t deviceState;
			streaming_dload_error_rx_t lastError;
			streaming_dload_log_rx_t   lastLog;

			const char* getNamedError(uint8_t code);
			const char* getNamedOpenMode(uint8_t mode);
			const char* getNamedMultiImage(uint8_t imageType);
			streaming_dload_device_state state;
	private:
		bool isValidResponse(uint8_t expectedCommand, uint8_t* response, size_t responseSize);
		bool isValidResponse(uint8_t expectedCommand, std::vector<uint8_t> &response);

    };
}

#endif // _SERIAL_STREAMING_DLOAD_SERIAL_H 
