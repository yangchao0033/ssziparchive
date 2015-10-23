//
//  SSZipArchive.h
//  SSZipArchive
//
//  Created by Sam Soffes on 7/21/10.
//  Copyright (c) Sam Soffes 2010-2015. All rights reserved.
//

#ifndef _SSZIPARCHIVE_H
#define _SSZIPARCHIVE_H

#import <Foundation/Foundation.h>
#include "unzip.h"

@protocol SSZipArchiveDelegate;

@interface SSZipArchive : NSObject

// Unzip
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination delegate:(id<SSZipArchiveDelegate>)delegate;

+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error;
+ (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error delegate:(id<SSZipArchiveDelegate>)delegate;

/** 解压缩进度控制 */
+ (BOOL)unzipFileAtPath:(NSString *)path
		  toDestination:(NSString *)destination
		progressHandler:(void (^)(NSString *entry, unz_file_info zipInfo, long entryNumber, long total))progressHandler
	  completionHandler:(void (^)(NSString *path, BOOL succeeded, NSError *error))completionHandler;
/** 解压缩，可控制进度，复写，密码 */
+ (BOOL)unzipFileAtPath:(NSString *)path
		  toDestination:(NSString *)destination
			  overwrite:(BOOL)overwrite
			   password:(NSString *)password
		progressHandler:(void (^)(NSString *entry, unz_file_info zipInfo, long entryNumber, long total))progressHandler
	  completionHandler:(void (^)(NSString *path, BOOL succeeded, NSError *error))completionHandler;

// Zip
/*!
 *  @author 杨超, 15-10-23 15:10:06
 *
 *  @brief  在指定文件路径下创建zip文件，添加在zip文件中的文件路径数组
 *
 *  @param path      zip路径
 *  @param filenames 需要压缩的文件名数组
 *
 *  @return 成功?YES:NO
 *
 *  @since <#version number#>
 */
+ (BOOL)createZipFileAtPath:(NSString *)path withFilesAtPaths:(NSArray *)filenames;
/*!
 *  @author 杨超, 15-10-23 15:10:41
 *
 *  @brief  在指定的文件路径下创建zip，将指定的文件夹压缩到zip文件中
 *
 *  @param path          zip存储创建路径
 *  @param directoryPath 需要压缩的文件夹
 *
 *  @return 成功?YES:NO
 *
 *  @since <#version number#>
 */
+ (BOOL)createZipFileAtPath:(NSString *)path withContentsOfDirectory:(NSString *)directoryPath;
/*!
 *  @author 杨超, 15-10-23 15:10:49
 *
 *  @brief  创建zip，并将目录压缩到zip中
 *
 *  @param path                <#path description#>
 *  @param directoryPath       <#directoryPath description#>
 *  @param keepParentDirectory <#keepParentDirectory description#>
 *
 *  @return <#return value description#>
 *
 *  @since <#version number#>
 */
+ (BOOL)createZipFileAtPath:(NSString *)path withContentsOfDirectory:(NSString *)directoryPath keepParentDirectory:(BOOL)keepParentDirectory;

- (id)initWithPath:(NSString *)path;
- (BOOL)open;
- (BOOL)writeFile:(NSString *)path;
- (BOOL)writeFileAtPath:(NSString *)path withFileName:(NSString *)fileName;
- (BOOL)writeData:(NSData *)data filename:(NSString *)filename;
- (BOOL)close;

@end

@protocol SSZipArchiveDelegate <NSObject>

@optional
/** 解压周期代理 */
- (void)zipArchiveWillUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo;
- (void)zipArchiveDidUnzipArchiveAtPath:(NSString *)path zipInfo:(unz_global_info)zipInfo unzippedPath:(NSString *)unzippedPath;

- (BOOL)zipArchiveShouldUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;
- (void)zipArchiveWillUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;
- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath fileInfo:(unz_file_info)fileInfo;
- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath unzippedFilePath:(NSString *)unzippedFilePath;
/** 压缩进度 */
- (void)zipArchiveProgressEvent:(unsigned long long)loaded total:(unsigned long long)total;
- (void)zipArchiveDidUnzipArchiveFile:(NSString *)zipFile entryPath:(NSString *)entryPath destPath:(NSString *)destPath;

@end

#endif /* _SSZIPARCHIVE_H */
