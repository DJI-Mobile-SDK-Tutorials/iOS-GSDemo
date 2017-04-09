//
//  DJIMediaFile.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIBaseProduct.h"
#import "DJICameraSettingsDef.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile;

/*********************************************************************************/
#pragma mark - DJIMediaType
/*********************************************************************************/

@class UIImage;


/**
 *  Media types.
 */
typedef NS_ENUM (NSUInteger, DJIMediaType){


    /**
     *  Unknown file type.
     */
    DJIMediaTypeUnknown,


    /**
     *  Image of JPEG format.
     */
    DJIMediaTypeJPEG,


    /**
     *  Video of MP4 format.
     */
    DJIMediaTypeMP4,


    /**
     *  Video of MOV format.
     */
    DJIMediaTypeMOV,


    /**
     *  Video of M4V format.
     */
    DJIMediaTypeM4V,


    /**
     *  Image of DNG format.
     */
    DJIMediaTypeRAWDNG,


    /**
     *  PANORAMA file type.
     */
    DJIMediaTypePanorama,


    /**
     *  Tiff file type.
     */
    DJIMediaTypeTIFF
};

/*********************************************************************************/
#pragma mark - DJIMediaVideoPlaybackStatus
/*********************************************************************************/


/**
 *  The playback status.
 */
typedef NS_ENUM(uint8_t, DJIMediaVideoPlaybackStatus) {


    /**
     *  The playback is stopped. No media is playing.
     */
    DJIMediaVideoPlaybackStatusStopped,


    /**
     *  The media manager is playing a video.
     */
    DJIMediaVideoPlaybackStatusPlaying,


    /**
     *  The playing video is paused.
     */
    DJIMediaVideoPlaybackStatusPaused,
};

/*********************************************************************************/
#pragma mark - DJIMediaVideoPlaybackState
/*********************************************************************************/


/**
 *  The playback state of the media manager.
 */
@interface DJIMediaVideoPlaybackState : NSObject


/**
 *  The video media file that is playing.
 *  
 *  @return An instance of `DJIMediaFile`.
 */
@property(nonatomic, readonly) DJIMediaFile *playingMedia;


/**
 *  The status of the playback (e.g. playing or paused).
 */
@property(nonatomic, readonly) DJIMediaVideoPlaybackStatus playbackStatus;


/**
 *  The playing position in seconds.
 */
@property(nonatomic, readonly) float playingPosition;

@end

/*********************************************************************************/
#pragma mark - DJIMediaFile
/*********************************************************************************/


/**
 *  This class contains information about a multi-media file on the SD card. It also
 *  provides methods to retrieve the  data in the file.
 */
@interface DJIMediaFile : NSObject


/**
 *  Get the file index used in the camera.
 */
@property(nonatomic, readonly) NSUInteger ID;


/**
 *  ID only used for sub-media files. For a sub-media, it will the same ID as its
 *  parent media.  Each sub-media file is distinguished by the sub-ID. For the other
 *  media file, it is always 0.
 */
@property(nonatomic, readonly) NSUInteger subID;


/**
 *  Returns the name of the media file in the SD Card.
 */
@property(nonatomic, readonly) NSString *_Nonnull fileName;


/**
 *  Returns the size, in bytes, of the media file.
 */
@property(nonatomic, readonly) long long fileSizeInBytes;


/**
 *  Returns the time when the media file was created as a string in the format
 *  "yyyy-MM-dd HH:mm:ss".
 */
@property(nonatomic, readonly) NSString *_Nonnull timeCreated;


/**
 *  If the media file is a video, this property returns the duration of the video in
 *  seconds. Will be 0s if the media  file is a photo.
 */
@property(nonatomic, readonly) float durationInSeconds;


/**
 *  Returns the type of media file.
 */
@property(nonatomic, readonly) DJIMediaType mediaType;


/**
 *  Returns the thumbnail for this media. If this property returns nil, call
 *  `fetchThumbnailWithCompletion`.
 */
@property(nonatomic, readonly) UIImage *_Nullable thumbnail;


/**
 *  The orientation of the camera when the video file was first recorded. If the
 *  camera orientation changes during a  video capture, this will report the initial
 *  orientation. Will be `DJICameraOrientationLandscape` if  the media file is a
 *  photo. Only Mavic Pro supports this property. Will be
 *  `DJICameraOrientationLandscape`  for other products.
 */
@property(nonatomic, readonly) DJICameraOrientation videoOrientation;


/**
 *  Camera resolution.
 */
@property(nonatomic, readonly) DJICameraVideoResolution resolution;


/**
 *  Frame rate when the media file is a video.
 *  
 *  @return An int value.
 */
@property(nonatomic, readonly) DJICameraVideoFrameRate frameRate;


/**
 *  Fetches this media's thumbnail with a resolution (99 x 99) from the SD card.
 *  This method can be used to fetch  either a photo or a video, where the first
 *  frame of the video is the thumbnail that is fetched. It is not  available if the
 *  media type is Panorama.
 *   Precondition:
 *   The camera mode is MediaDownload mode.
 *   Post Condition:
 *   This method will start to download the media thumbnail in the SD card. The
 *  content  can be videos or images.
 *  
 *  @param completion Completion block.
 */
- (void)fetchThumbnailWithCompletion:(DJICompletionBlock)completion;


/**
 *  Fetches this media's data from the SD card. The difference between fetching the
 *  media data and fetching the  thumbnail is that fetching the thumbnail will
 *  return a low-resolution image of the actual picture, while fetching  the media
 *  data will return all data for a video or image.
 *  
 *  @param data The media's data.
 *  @param stop The BOOL value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)fetchMediaDataWithCompletion:(void (^_Nonnull)(NSData *_Nullable data, BOOL *_Nullable stop, NSError *_Nullable error))completion;


/**
 *  Fetch media's preview image. The preview image is a lower resolution (960 x 540)
 *  version of a still picture or the first frame of a video. The `DJIMediaType` of
 *  this media object should be `DJIMediaTypeJPEG`. It is not available if the media
 *  type is `DJIMediaTypePanorama`.
 *  
 *  @param image The UIImage object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)fetchPreviewImageWithCompletion:(void (^_Nonnull)(UIImage *image, NSError *_Nullable error))completion;


/**
 *  Fetch sub media files. It is available only when the media type is
 *  `DJIMediaTypePanorama`.  User should use this method to fetch the set of photos
 *  shot in a panorama mission.
 *   Precondition:
 *   The camera  mode should be set as `DJICameraModeMediaDownload` mode.
 *  
 *  @param mediaList The array of the DJIMedia objects.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)fetchSubMediaFileListWithCompletion:(void (^_Nonnull)(NSArray<DJIMediaFile *> *_Nullable mediaList, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
