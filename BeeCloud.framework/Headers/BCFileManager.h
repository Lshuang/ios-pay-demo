//
//  BCFileManager.h
//  BeeCloud
//
//  Created by Junxian Huang on 10/7/14.
//  Copyright (c) 2014 BeeCloud Inc. All rights reserved.
//

#import "BCFile.h"

/**
 *  Manages file upload.
 */
@interface BCFileManager : NSObject

#pragma mark - Upload file content to cloud
/** @name Upload File Content to Cloud */

/**
 *  Upload file to cloud in the background, with the given file path and the new file name to set this file to. The file
 *  name in the cloud should be unique, and uploading a file A with the same name as the existing file B in the cloud
 *  will cause A to replace B. The generated BCFile object is a row in the "file__" table in BeeCloud representing a
 *  file object, which contains all metadata information of this file, plus any user-defined file attributes.
 *
 *  @param filePath The local file path of the file to be uploaded.
 *  @param bucket   The globally unique Qiniu bucket to upload this file to. This must not be nil or empty string.
 *  @param name     The unique file name to set this file to; if set to nil, the original file name will be used.
 *
 *  @return The newly created or updated (if the file with the same name exists in the given bucket) BCFile object; or
 *          nil if the upload fail.
 */
+ (BCFile *)uploadFileInBackground:(NSString *)filePath toBucket:(NSString *)bucket renameTo:(NSString *)name;

/**
 *  Upload file to cloud in the background, with the given file path and the new file name to set this file to. The file
 *  name in the cloud should be unique, and uploading a file A with the same name as the existing file B in the cloud
 *  will cause A to replace B. The generated BCFile object is a row in the "file__" table in BeeCloud representing a
 *  file object, which contains all metadata information of this file, plus any user-defined file attributes.
 *
 *  @param filePath The local file path of the file to be uploaded.
 *  @param bucket   The globally unique Qiniu bucket to upload this file to. This must not be nil or empty string.
 *  @param name     The unique file name to set this file to; if set to nil, the original file name will be used.
 *  @param block    The callback block can either be nil or should have the following argument signature:
 *                  (BOOL succeeded, NSError *error)
 *                  It will report the whether the upload is successful with error being nil, or report the error
 *                  otherwise.
 *
 *  @return The newly created or updated (if the file with the same name exists in the given bucket) BCFile object; or
 *          nil if the upload fail.
 */
+ (BCFile *)uploadFileInBackground:(NSString *)filePath toBucket:(NSString *)bucket renameTo:(NSString *)name
                     withBlock:(BCBooleanResultBlock)block;

/**
 *  Upload file to cloud in the background, with the given file data and the new file name to set this file to. The file
 *  name in the cloud should be unique, and uploading a file A with the same name as the existing file B in the cloud
 *  will cause A to replace B. The generated BCFile object is a row in the "file__" table in BeeCloud representing a
 *  file object, which contains all metadata information of this file, plus any user-defined file attributes.
 *
 *  @param fileData The local file data of the file to be uploaded.
 *  @param bucket   The globally unique Qiniu bucket to upload this file to. This must not be nil or empty string.
 *  @param name     The unique file name to set this file to; it can not be nil.
 *
 *  @return The newly created or updated (if the file with the same name exists in the given bucket) BCFile object; or 
 *          nil if the upload fail.
 */
+ (BCFile *)uploadFileDataInBackground:(NSData *)fileData toBucket:(NSString *)bucket renameTo:(NSString *)name;

/**
 *  Upload file to cloud in the background, with the given file data and the new file name to set this file to. The file
 *  name in the cloud should be unique, and uploading a file A with the same name as the existing file B in the cloud
 *  will cause A to replace B. The generated BCFile object is a row in the "file__" table in BeeCloud representing a
 *  file object, which contains all metadata information of this file, plus any user-defined file attributes.
 *
 *  @param fileData The local file data of the file to be uploaded.
 *  @param bucket   The globally unique Qiniu bucket to upload this file to. This must not be nil or empty string.
 *  @param name     The unique file name to set this file to; it can not be nil.
 *  @param block    The callback block can either be nil or should have the following argument signature:
 *                  (BOOL succeeded, NSError *error)
 *                  It will report the whether the upload is successful with error being nil, or report the error
 *                  otherwise.
 *
 *  @return The newly created or updated (if the file with the same name exists in the given bucket) BCFile object; or
 *          nil if the upload fail.
 */
+ (BCFile *)uploadFileDataInBackground:(NSData *)fileData toBucket:(NSString *)bucket renameTo:(NSString *)name
                         withBlock:(BCBooleanResultBlock)block;

@end
