//
//  BCUser.h
//  BeeCloud SDK
//
//  Created by Junxian Huang on 2/20/14.
//  Copyright (c) 2014 BeeCloud Inc. All rights reserved.
//

#import "BCConstants.h"
#import "BCObject.h"

@interface BCUser : BCObject
/** @name Class Property */
 
/*!
 The session token for the BCUser. This is set by the server upon successful authentication.
 */
@property (nonatomic, strong) NSString *sessionToken;

/*! 
 The username for the BCUser. Normally, this is an email address.
 */
@property (nonatomic, strong) NSString *userNickName;

/*!
 The password for the BCUser. This will not be filled in from the server with
 the password. It is only meant to be set.
 */
@property (nonatomic, strong) NSString *password;

/*!
 The email for the BCUser.
 */
@property (nonatomic, strong) NSString *email;

#pragma mark - Create new user
/** @name Creating A New User */

/**
 *  Creates a new BCUser object, with a randomly generated userId.
 *
 *  @return Return a new BCUser object.
 */
+ (instancetype)user;

/**
 *  Creates a new BCUser object with the given userId. The user with the given ID may or may not exist in the cloud. If you
    want to download all user information from the cloud, call the refresh function. If the given ID does not exist in the
    cloud, the refresh function will fail and do nothing. A successful refresh is required before you can save this object.
    Without successful refresh, you can still modify the content of this object, but you can't save to the cloud.
    @warning Local cached copy may be used if you have created this user previously. To make sure that the cached copy is
    not used, use "BCUser *user = [[BCUser alloc] initWithUserId];" or clear cache via "[BeeCloud clearAllCache];".
 *
 *  @param objectId The objectId must be an UUID in the format of "550e8400-e29b-41d4-a716-446655440000".
 *  @param cache   YES if you want to get the instance from the cache
 *
 *  @return Return a new BCUser object.
 */
+ (instancetype)userWithObjectId:(NSString *)objectId usingCache:(BOOL)cache;

/**
 *  Initializes a new BCUser object, with a randomly generated userId.
 *
 *  @return Returns a new BCUser object.
 */
- (instancetype)init;

/**
 *  Initializes a new BCUser object with the given userId. The user with the given ID may or may not exist in the cloud. If
 you want to download all user information from the cloud, call the refresh function. If the given ID does not exist in
 the cloud, the refresh function will fail and do nothing. A successful refresh is required before you can save this
 object. Without successful refresh, you can still modify the content of this object, but you can't save to the cloud.
 *
 *  @param objectId The objectId must be an UUID in the format of "550e8400-e29b-41d4-a716-446655440000".
 *
 *  @return Returns a new BCUser object.
 */
- (instancetype)initWithObjectId:(NSString *)objectId;

#pragma mark - sign up
/** @name Sign Up */

/**
 *  Signs up the user. Make sure that password and email are set. This requires that the email isn't already taken.
 *
 *  @param email    the email will be signed up.
 *  @param password the account's password
 *
 *  @return Returns whether the sign up was successful.
 */

+ (BOOL)signUpWithEmail:(NSString *)email password:(NSString *)password;

/**
 *  Signs up the user. Make sure that password and username are set. This requires that the username isn't already taken.
 *
 *  @param email    the email will be signed up.
 *  @param password the account's password
 *  @param error Error object to set on error.
 *
 *  @return Returns whether the sign up was successful.
 */
+ (BOOL)signUpWithEmail:(NSString *)email password:(NSString *)password error:(NSError **)error;

/*!
    Signs up the user asynchronously. Make sure that password and username are set. This requires that the username isn't
already taken.
 *  @param email    the email will be signed up.
 *  @param password the account's password
 *  @param block The block to execute. The block should have the following argument signature:
    (BOOL succeeded, NSError *error)
 */
+ (void)signUpInBackgroundWithEmail:(NSString *)email password:(NSString *)password block:(BCBooleanResultBlock)block;

#pragma mark - Check email availability
/** @name Check Email Availability */

/**
 *  Check whether this email is available for user to use. The emails that exist in the cloud are not available.
 *
 *  @param email email string
 *
 *  @return YES if the email is available.
 */
+ (BOOL)checkEmailAvailability:(NSString *)email;

/**
 *  Check whether this email is available for user to use. The emails that exist in the cloud are not available.
 *
 *  @param email email string
 *  @param error Error object to set on error.
 *
 *  @return YES if the email is available.
 */
+ (BOOL)checkEmailIsExist:(NSString *)email error:(NSError **)error;

/**
 *  Check whether this email is available for user to use. The emails that exist in the cloud are not available.
 *
 *  @param email email string
 *  @param block The block to execute. The block should have the following argument signature:
 *               (BOOL available, NSError *error)
 */
+ (void)checkEmailAvailability:(NSString *)email withBlock:(BCBooleanResultBlock)block;

#pragma mark - Accessing current user
/** @name Accessing The Current User */

/**
 *  Gets the currently logged in user and returns an instance of it.
 *
 *  @return Returns a BCUser that is the currently logged in user. If there is none, returns nil;
 */
+ (instancetype)currentUser;

#pragma mark - Email verification
/** @name Requesting an Email Verification */

/// @todo(hjx).

#pragma mark - Logging in
/** @name Logging in */

/**
 *   Makes a request to login a user with specified credentials. Returns an instance of the successfully logged in BCUser.This will also cache the user locally so that calls to currentUser will use the latest logged in user.
 *
 *  @param email    The email of the user
 *  @param password The password of the user
 *
 *  @return Returns YES if login successed. If login failed for either wrong password or wrong username,
 */
+ (BOOL)logInWithEmail:(NSString *)email
              password:(NSString *)password;

/**
 *   Makes a request to login a user with specified credentials. Returns an instance of the successfully logged in BCUser.This will also cache the user locally so that calls to currentUser will use the latest logged in user.
 *
 *  @param email    The email of the user
 *  @param password The password of the user
 *  @param error    The error object to set on error.
 *
 *  @return Returns YES if login successed. If login failed for either wrong password or wrong username,
 */
+ (BOOL)logInWithEmail:(NSString *)email
              password:(NSString *)password
                 error:(NSError **)error;

/**
 *   Makes a request to login a user with specified credentials. Returns an instance of the successfully logged in BCUser.This will also cache the user locally so that calls to currentUser will use the latest logged in user.
 *
 *  @param email    The email of the user
 *  @param password The password of the user
 *  @param block    block The block to execute. The block should have the following argument signature:
    (BOOL succeeded, NSError *error)
 *
 *  @return Returns YES if login successed. If login failed for either wrong password or wrong username,
 */
+ (void)logInWithEmailInBackground:(NSString *)email
                          password:(NSString *)password
                         withBlock:(BCBooleanResultBlock)block;

#pragma mark - Logging out
/** @name Logging Out */

/**
 *  logout the currentUser
 *
 *  @return YES if logout is successed.
 */
+ (BOOL)logOut;

/**
 *  logout the currentUser
 *
 *  @param error The error object to set on error.
 *
 *  @return YES if logout is successed.
 */
+ (BOOL)logOutWithError:(NSError **)error;

/**
 *  logout the currentUser in background
 *
 *  @param block  block The block to execute. The block should have the following argument signature:
 (BOOL succeeded, NSError *error)
 */
+ (void)logOutWithBlock:(BCBooleanResultBlock)block;

#pragma mark - Password reset
/** @name Requesting a Password Reset */

/**
 *  Send a password reset request for the given email. If a user account exists with that email, an email will be sent to that address with instructions on how to reset their password.
 *
 *  @param email Email of the account to send a reset password request.
 *
 *  @return Returns true if the reset email request is successful. False if no account was found for the email address.
 */
+ (BOOL)requestPasswordResetForEmail:(NSString *)email;

/**
 *  Send a password reset request for the given email and sets an error object. If a user account exists with that email, an email will be sent to that address with instructions on how to reset their password.
 *
 *  @param email Email of the account to send a reset password request.
 *  @param error The error object to set on error.
 *
 *  @return Returns true if the reset email request is successful. False if no account was found for the email address.
 */
+ (BOOL)requestPasswordResetForEmail:(NSString *)email
                               error:(NSError **)error;

/**
 *  Send a password reset request asynchronously for the given email. If a user account exists with that email, an email will be sent to that address with instructions on how to reset their password.
 *
 *  @param email Email of the account to send a reset password request.
 *  @param block block The block to execute. The block should have the following argument signature:
 (BOOL succeeded, NSError *error)
 */
+ (void)requestPasswordResetForEmailInBackground:(NSString *)email
                                           block:(BCBooleanResultBlock)block;

@end
