
#ifndef __JODOWNLOADER__
#define __JODOWNLOADER__

#include <string>
#include <functional>
#include <mutex>

#include "utils/JOMacro.h"
#include "utils/JOLock.h"

namespace cocos2d { namespace network {
    class Downloader;
	class DownloadTask;
}}

NS_JOFW_BEGIN


/*
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And there should be a file named
 *  version in the server, which contains version code.
 */
class JO_DLL JODownloader 
{
public:
    enum class ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        CREATE_FILE,
        /** Error caused by network
         -- network unavailable
         -- timeout
         -- ...
         */
        NETWORK,
        /** There is not a new version
         */
        NO_NEW_VERSION,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        UNCOMPRESS,
		MD5_ERROR, // add by James
    };
    
	typedef std::function<void(std::string&, int)> ErrorCall;
	typedef std::function<void(std::string&, int)> ProgressCall;
	typedef std::function<void(std::string&)> SuccessCall;
	typedef std::function<void(std::string&, unsigned int, unsigned int)> UnzipProgressCall;


	JODownloader();
	virtual ~JODownloader();

	void setCall(ErrorCall errorCallback, ProgressCall progressCallback, SuccessCall successCallback, UnzipProgressCall unzipProgressCall);
    
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */

	bool checkUpdate();
    

	void setReplacePath(const char* oldPath, const char* newPath);
	inline void setMd5(std::string md5String){ _md5String = md5String; };

    /* @brief Gets url of package.
     */
	inline const char* getPackageUrl() const{ return _packageUrl.c_str(); };
    
    /* @brief Sets package url.
     */
	inline void setPackageUrl(const char* packageUrl){ _packageUrl = packageUrl; };
    
    /* @brief Gets storage path.
     */
	inline const char* getStoragePath() const{ return _storagePath.c_str(); };
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief Sets connection time out in seconds
     */
	inline void setConnectionTimeout(unsigned int timeout){ _connectionTimeout = timeout; };
    
    /** @brief Gets connection time out in seconds
     */
	inline unsigned int getConnectionTimeout(){ return _connectionTimeout; };
    

protected:
    void checkStoragePath();
	void _onHandleDownloadSuccess(const std::string& filepath);
	bool uncompress(const std::string& filepath);
    void setSearchPath();
	void downloadAndUncompress(const std::string& filepath);

private:
	unsigned int m_sn;
	ErrorCall errorCall;
	ProgressCall progressCall;
	SuccessCall successCall;
	UnzipProgressCall unzipProgressCall;


    std::string _storagePath;    
    std::string _packageUrl;
    
    cocos2d::network::Downloader* _downloader;

    unsigned int _connectionTimeout;
    bool _isDownloading;

	//! Replace path
	JOLock		m_replaceLock;
	std::string _oldeReplacePath;
	std::string _newReplacePath;

	std::string _md5String;

};


NS_JOFW_END

#endif __JODOWNLOADER__
