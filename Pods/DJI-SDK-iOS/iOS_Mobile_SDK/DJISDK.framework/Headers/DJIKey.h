//
//  DJIKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define EXTERN_KEY       extern __attribute__((visibility("default")))

EXTERN_KEY NSString *const DJIParamConnection;


/**
 *  Base class of all keys to be used with the keyed interface and the
 *  `DJIKeyManager`.
 */
@interface DJIKey : NSObject


/**
 *  Defines wether or not the key is to be used with components of the  product
 */
@property (nonatomic) BOOL isComponentKey;


/**
 *  Defines wether or not the key is to be used with missions. (Mission Control
 *  only)
 */
@property (nonatomic) BOOL isMissionKey;


/**
 *  The param part of the key.
 */
@property (readonly, nonatomic, nullable) NSString *param;


/**
 *  Convenience creator of a key by only specifying the param to be used.
 *   This is mostly useful in DJIKey subclasses.
 *  
 *  @param param A valid String-formatted key as defined in DJIKey's subclasses headers
 *  
 *  @return A valid key object or `nil` if an error occured.
 */
+ (nullable instancetype)keyWithParam:(nonnull NSString *)param;


/**
 *  Convenience creator of a key by specifying the index of the element and the
 *  parameter of the key
 *  
 *  @param index the index of the element. In the case of multiple components these would refer to their index.
 *  @param param A valid string-formatted key as defined in DJIKey's subclasses headers.
 *  
 *  @return A valid key object or nil if an error occured.
 */
+ (nullable instancetype)keyWithIndex:(NSInteger)index
                             andParam:(nonnull NSString *)param;

/**
 *  Full creator of a key allowing to specify subelement, subindex and parameters.
 *  
 *  @param index The index of the element
 *  @param subElement The sub element string-formatted key as defined in DJIKey's subclasses headers.
 *  @param subIndex The sub element index.
 *  @param param The string-formatted key as defined in DJIKey's subclasses headers.
 *  
 *  @return A valid key object or nil if an error occured.
 */
+ (nullable instancetype)keyWithIndex:(NSInteger)index
                           subElement:(nonnull NSString *)subElement
                             subIndex:(NSInteger)subIndex
                             andParam:(nonnull NSString *)param;

@end

NS_ASSUME_NONNULL_END
