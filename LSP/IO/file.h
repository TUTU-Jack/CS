#ifndef _FILE_H_
#define _FILE_H_

#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

void cp1(const char *inputFileName,const char *outputFileName);
/**
 * @brief  复制文件内容
 * @note   
 * @param  *inputFileName: 
 * @param  *outputFileName: 
 * @retval None
 */
void cp(const char *inputFileName,const char *outputFileName);

/**
 * @brief  将文件权限转换为字符
 * @note   
 * @param  mode: 
 * @param  *str: 
 * @retval None
 */
void mode_to_letters(mode_t mode,char *str);

/**
 * @brief  将用户ID转换为用户名
 * @note   
 * @param  uid: 
 * @retval 
 */
const char *uid_to_name(uid_t uid);

/**
 * @brief  将组ID转换为组名
 * @note   
 * @param  gid: 
 * @retval 
 */
const char *gid_to_name(gid_t gid);

/**
 * @brief  显示文件信息
 * @note   
 * @param  *buf: 
 * @retval None
 */
void show_fileInfo(const char *filename,void *buf);

/**
 * @brief  列出目录下的所有文件
 * @note   
 * @param  *dirname: 
 * @param  argc: 
 * @retval None
 */
void ls(const char *dirname,char *arg);

void IOselect();

#endif