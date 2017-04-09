//
//  DJIVideoFeeder.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The video feed physical source.
 */
typedef NS_ENUM(NSInteger, DJIVideoFeedPhysicalSource) {

    /**
     *  Main Camera.
     */
    DJIVideoFeedPhysicalSourceMainCamera,


    /**
     *  FPV Camera.
     */
    DJIVideoFeedPhysicalSourceFPVCamera,


    /**
     *  Lightbridge video channel.
     */
    DJIVideoFeedPhysicalSourceLB,


    /**
     *  EXT video channel.
     */
    DJIVideoFeedPhysicalSourceEXT,


    /**
     *  HDMI video channel.
     */
    DJIVideoFeedPhysicalSourceHDMI,


    /**
     *  AV video channel.
     */
    DJIVideoFeedPhysicalSourceAV,

    /**
     *  Unknown video channel.
     */
    DJIVideoFeedPhysicalSourceUnknown
};

@class DJIVideoFeed;


/**
 *  Listener that receives notifications when a new video physical source becomes
 *  available.
 */
@protocol DJIVideoFeedSourceListener <NSObject>


/**
 *  Called when a video feed is made available from a new physical source.
 *  
 *  @param videoFeed A `DJIVideoFeed` object.
 *  @param physicalSource An enum value of `DJIVideoFeedPhysicalSource`.
 */
- (void)videoFeed:(nonnull DJIVideoFeed *)videoFeed didChangePhysicalSource:(DJIVideoFeedPhysicalSource)physicalSource;

@end


/**
 *  Represents a single video feed from a single channel or port.
 */
@protocol DJIVideoFeedListener <NSObject>


/**
 *  Called when the video feed receives new video data.
 *  
 *  @param videoFeed A `DJIVideoFeed` object.
 *  @param videoData An NSData object of video data.
 */
- (void)videoFeed:(nonnull DJIVideoFeed *)videoFeed didUpdateVideoData:(nonnull NSData *)videoData;

@end


/**
 *  DJIVideoFeed.
 */
@interface DJIVideoFeed : NSObject


/**
 *  The video feed physical source.
 */
@property (nonatomic, assign, readonly) DJIVideoFeedPhysicalSource physicalSource;


/**
 *  Add Listener for video feed.
 *  
 *  @param videoFeedListener The protocol of `DJIVideoFeedListener`.
 *  @param queue A dispatch_queue_t.
 */
- (void)addListener:(id <DJIVideoFeedListener>)videoFeedListener withQueue:(nullable dispatch_queue_t)queue;


/**
 *  Remove Listener for video feed.
 *  
 *  @param videoFeedListener The protocol of `DJIVideoFeedListener`.
 */
- (void)removeListener:(id <DJIVideoFeedListener>)videoFeedListener;


/**
 *  Remove all Listeners for video feed.
 */
- (void)removeAllListeners;

@end


/**
 *  Class that handles live video streams from product to mobile device.
 */
@interface DJIVideoFeeder : NSObject


/**
 *  The primary video feed.
 */
@property (nonatomic, strong, nonnull) DJIVideoFeed *primaryVideoFeed;


/**
 *  The secondary video feed.
 */
@property (nonatomic, strong, nonnull) DJIVideoFeed *secondaryVideoFeed;


/**
 *  Add Video Feed Source Listener.
 *  
 *  @param sourceListener The protocol of `DJIVideoFeedSourceListener`.
 */
- (void)addVideoFeedSourceListener:(id <DJIVideoFeedSourceListener>)sourceListener;


/**
 *  Remove Video Feed Source Listener.
 *  
 *  @param sourceListener The protocol of `DJIVideoFeedSourceListener`.
 */
- (void)removeVideoFeedSourceListener:(id <DJIVideoFeedSourceListener>)sourceListener;


/**
 *  Remove all listeners.
 */
- (void)removeAllListeners;

@end

NS_ASSUME_NONNULL_END
