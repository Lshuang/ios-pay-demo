//
//  BCAnalysis.h
//  BeeCloud
//
//  Created by Junxian Huang on 8/18/14.
//  Copyright (c) 2014 BeeCloud Inc. All rights reserved.
//

/**
 *  BCAnalysis framework provides easy ways for app developers to log user behaviors and the results will be analyzed
 *  and presented in BeeCloud website.
 */
@interface BCAnalysis : NSObject

/**
 *  If your app requires user login, call this method whenever a user is successfully authenticated. This will help us
 *  provide you better user analysis.
 *
 *  @param userId User ID in the environment of your app, it could be email, or any other unique ID to identify this
 *                user.
 */
+ (void)setUserId:(NSString *)userId;

/**
 *  Tells us whether this user is paid user, if possible.
 *
 *  @param isPaidUser YES if this user is paid user; NO otherwise.
 */
+ (void)setIsPaidUser:(BOOL)isPaidUser;

/**
 *  Tells us whether this user is male, if possible.
 *
 *  @param isMale YES if this user is male; NO otherwise.
 */
+ (void)setUserGender:(BOOL)isMale;

/**
 *  Tells us the age of this user, e.g., 15.5, if possible
 *
 *  @param age Age in the number of years.
 */
+ (void)setUserAge:(double)age;

/**
 *  Log an event. For the event that user A clicked "like" on image B, the entity is B and event could be "like_image".
 *
 *  @param event  Event name, such as "posting_photo", which should not be nil.
 *  @param entity Target entity ID of this event, e.g., the image ID of a user viewing image event, or nil if nothing to
 *                specify.
 *  @param note   Optional note for debugging information, or nil if nothing to specify.
 *
 */
+ (void)logEvent:(NSString *)event towardsEntity:(NSString *)entity withNote:(NSString *)note;

@end
