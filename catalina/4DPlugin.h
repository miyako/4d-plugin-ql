/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.h
 #	source generated by 4D Plugin Wizard
 #	Project : QL
 #	author : miyako
 #	2017/10/07
 #
 # --------------------------------------------------------------------------------*/

#import <QuickLook/QuickLook.h>
#import <Quartz/Quartz.h>

#import "libjson.h"

/*
 because we are using private APIs, it is imperative that...
 1. we compile as obj-c (not obj-c++)
 2. we don't use .pch or carbon framework
 */

typedef struct __QLPreview *QLPreviewRef;

@protocol QLDataGenerationHandler
- (void)startAttachment:(NSURL *)arg1 withMimeType:(NSString *)arg2 encoding:(NSString *)arg3;
- (void)receivedDataFromServer:(NSData *)arg1 attachmentURL:(NSURL *)arg2 hasMoreData:(BOOL)arg3;
@end

@protocol QLDaemonProxyProtocol
- (void)requestDataForPreview:(NSUUID *)arg1 dataHandler:(id <QLDataGenerationHandler>)arg2;
@end

@interface QLDaemonProxy : NSObject
{
    NSXPCConnection *_connection;
    NSObject<QLDaemonProxyProtocol> *_proxy;
}

+ (id)interface;
+ (id)sharedInstance;
//- (void).cxx_destruct;
- (id)forwardingTargetForSelector:(SEL)arg1;
- (void)dealloc;
- (id)init;

@end

typedef void (^CDUnknownBlockType)(void); // return type and parameters are unknown

@interface QLPreviewProgressiveCallbacks : NSObject
{
    CDUnknownBlockType _startDataRepresentation;
    CDUnknownBlockType _startAttachment;
    CDUnknownBlockType _appendData;
    CDUnknownBlockType _createSafeAttachmentURL;
}

@property(copy, nonatomic) CDUnknownBlockType createSafeAttachmentURL; // @synthesize createSafeAttachmentURL=_createSafeAttachmentURL;
@property(copy, nonatomic) CDUnknownBlockType appendData; // @synthesize appendData=_appendData;
@property(copy, nonatomic) CDUnknownBlockType startAttachment; // @synthesize startAttachment=_startAttachment;
@property(copy, nonatomic) CDUnknownBlockType startDataRepresentation; // @synthesize startDataRepresentation=_startDataRepresentation;
//- (void).cxx_destruct;

@end

@interface QLPreview : NSObject <NSSecureCoding, QLDataGenerationHandler>
{
    struct __QLPreview *_previewRef;
    QLDaemonProxy *_daemonProxy;
    NSUUID *_uuid;
    NSMutableArray *_waitForDataCompletionBlocks;
    NSDictionary *_waitForDataOptions;
    BOOL _progressive;
    QLPreviewProgressiveCallbacks *_progressiveCallbacks;
}

- (id)synchronousGetData;
- (id)initWithQLPreviewRef:(struct __QLPreview *)arg1;

@property struct __QLPreview *previewRef;

@end

QL_PRIVATE_EXPORT QLPreviewRef QLPreviewCreate(CFAllocatorRef, CFURLRef, CFDictionaryRef);
QL_PRIVATE_EXPORT void QLPreviewClose(QLPreviewRef);
QL_PRIVATE_EXPORT CFDictionaryRef QLPreviewCopyProperties(QLPreviewRef);
QL_PRIVATE_EXPORT CFStringRef QLPreviewCopyPreviewContentType(QLPreviewRef);
QL_PRIVATE_EXPORT CFStringRef QLPreviewGetDisplayBundleID(QLPreviewRef);
QL_PRIVATE_EXPORT CFStringRef QLPreviewTypeGetRawImageDisplayBundleID();
QL_PRIVATE_EXPORT CFStringRef QLPreviewTypeGetRawImageContentType();
QL_PRIVATE_EXPORT CFIndex QLPreviewTypeGetDisplayBundleCount();

// --- QL
void QL_Create_thumbnail(PA_PluginParameters params);
void QL_Create_preview(PA_PluginParameters params);
