//
//  BCFile.h
//  BeeCloud
//
//  Created by Junxian Huang on 7/23/14.
//  Copyright (c) 2014 BeeCloud Inc. All rights reserved.
//

#import "BCObject.h"

/**
 *  BCFile framework provides easy methods to upload files to cloud (via BCFileManager), modify file metadata, access
 *  the file URLs so as to make them accessible.
 *
 *  Notice that the actual file content, e.g., the binary data of an image file, is not stored inside a BCFile object,
 *  instead a BCFile object is a file record containing all metadata information of a file, and the actual content of
 *  the file is accessed via the file URL.
 *
 *  BCFile extends BCObject class, so all properties and methods from BCObject can be used in BCFile. All BCFile records
 *  will be shown in the "file__" system table in BeeCloud website dashboard.
 */
@interface BCFile : BCObject

#pragma mark - Properties
/** @name Class Properties */

/**
 *  The URL of this file. If the file has not been uploaded before or this file object has not been refreshed, the URL
 *  is nil.
 */
@property (nonatomic, strong, readonly) NSString *URL;

/**
 *  The size of this file. If the file has not been uploaded before or this file object has not been refreshed, the size
 *  is 0.
 */
@property (nonatomic, readonly) long long fileSize;

/**
 *  The name of this file. If the file has not been uploaded before or this file object has not been refreshed, the name
 *  is nil.
 */
@property (nonatomic, strong, readonly) NSString *fileName;

/**
 *  The extension of this file. If the file has not been uploaded before or this file object has not been refreshed, the
 *  extension is nil.
 */
@property (nonatomic, strong, readonly) NSString *fileExtension;

/**
 *  The status of this file. If the file has not been uploaded before or this file object has not been refreshed, the
 *  status is BCFileStatusDefault.
 */
@property (nonatomic, readonly) BCFileStatus fileStatus;

#pragma mark - Create instances
/** @name Create File Instances */

/**
 *  Creates a BCFile object representing the metadata record of a file. If the URL exists in the cloud, the existing
 *  BCFile object will be loaded; otherwise, a new BCFile object will be created in the cloud. Each URL is unique within
 *  each application.
 *
 *  In case there are multiple rows in file__ table with the same URL, only the oldest row will be retained and the rest
 *  will be deleted, as URL must be unique in the cloud.
 *
 *  @param url The file URL, which must be a valid URL pointing to this file.
 *
 *  @return The instantiated local BCFile object.
 */
+ (instancetype)fileWithURL:(NSString *)url;

/**
 *  Creates an existing BCFile object that exists in the cloud with the given objectId. If you want to download all
 *  object information from the cloud, call the refresh function. If the given ID does not exist in the cloud, the
 *  refresh function will fail and do nothing.
 *
 *  @param objectId The objectId must be an UUID in the format of "550e8400-e29b-41d4-a716-446655440000".
 *  @param cache    Specifies whether to use local cached copy of this object if you have created this object
 *  previously. To make sure that the cached copy is not used, set cache to NO. You can clear all caches via
 *  "[BeeCloud clearAllCache];".
 *
 *  @return The instantiated local BCFile object with the given objectId.
 */
+ (instancetype)existingFileWithObjectId:(NSString *)objectId usingCache:(BOOL)cache;

/**
 *  Initializes a new BCFile object representing the metadata record of a file. This object is not synced to the cloud
 *  until the save methods are called, similar to BCObject.
 *
 *  @return The instantiated local BCFile object.
 */
- (instancetype)init;

/**
 *  Initializes an existing BCFile object that exists in the cloud with the given objectId. If you want to download all
 *  object information from the cloud, call the refresh function. If the given ID does not exist in the cloud, the
 *  refresh function will fail and do nothing.
 *
 *  @param objectId The objectId must be an UUID in the format of "550e8400-e29b-41d4-a716-446655440000".
 *  @param cache    Specifies whether to use local cached copy of this object if you have created this object
 *  previously. To make sure that the cached copy is not used, set cache to NO. You can clear all caches via
 *  "[BeeCloud clearAllCache];".
 *
 *  @return The instantiated local BCFile object with the given objectId.
 */
- (instancetype)initWithObjectId:(NSString *)objectId;

@end
