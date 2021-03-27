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

struct __QLRequest {
    struct __CFRuntimeBase {
        unsigned long long _field1;
        _Atomic unsigned long long _field2;
    } _field1;
    id _field2;
    unsigned int _field3;
    struct {
        unsigned int _field1[8];
    } _field4;
    struct __CFURL *_field5;
    struct __CFURL *_field6;
    struct __CFURL *_field7;
    void *_field8;
    struct __CFString *_field9;
    struct __CFDictionary *_field10;
    struct __CFString *_field11;
    struct __CFString *_field12;
    unsigned char _field13;
    struct __QLGenerator *_field14;
    struct __CFDictionary *_field15;
    struct CGContext *_field16;
    void (*_field17)(void);
    void *_field18;
    struct {
        long long _field1;
        void (*_field2)(void);
        void (*_field3)(void);
        void (*_field4)(void);
        void (*_field5)(void);
    } _field19;
    unsigned long long _field20;
    unsigned char _field21;
    unsigned char _field22;
    unsigned char _field23;
    unsigned char _field24;
    unsigned char _field25;
    unsigned char _field26;
    unsigned char _field27;
    unsigned char _field28;
};

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
- (id)initWithURL:(NSURL *)url options:(NSDictionary *)options;

@end

// --- QL
void QL_Create_thumbnail(PA_PluginParameters params);
void QL_Create_preview(PA_PluginParameters params);

/**
 
 Contents of (__DATA,__objc_selrefs) section
     0x100019cdd sharedInstance
     0x100019cec print:
     0x100019cf3 initWithContentsOfURL:
     0x100019d0a printErr:
     0x100019d14 componentsJoinedByString:
     0x100019d2e statisticsWithNames:
     0x100019d43 resetWithNames:
     0x100019d53 stopServerThreadImmediately
     0x100019d6f forcedContentTypeUTI
     0x100019d84 initWithUUIDBytes:
     0x100019d97 forcedGenerator
     0x100019da7 handleRequest:withQoS:
     0x100019dbe dealloc
     0x100019dc6 bounds
     0x100019dcd compareWith1x
     0x100019ddb currentContext
     0x100019dea graphicsPort
     0x100019df7 showRects
     0x100019e01 baselineOffsetFromBottom
     0x100019ead testUtility
     0x100019eb9 generateThumbnailLocally:statusHandler:completionHandler:
     0x100019ef3 sessionFromUUID:
     0x100019f04 receivedDataFromServer:attachmentURL:hasMoreData:
     0x100019f36 handleGetData:
     0x10001a12c init
     0x10001a131 setPrefersAutoPagination:
     0x10001a14b setForcedContentTypeUTI:
     0x10001a164 setForcedGeneratorPath:
     0x10001a17c setOutputFolder:
     0x10001a18d setArguments:
     0x10001a19b setServerName:
     0x10001a1aa generateCacheFile
     0x10001a1bc initWithFormat:arguments:
     0x10001a1d6 _printToStream:format:argList:
     0x10001a1f5 array
     0x10001a1fb defaultManager
     0x10001a20a stringWithFileSystemRepresentation:length:
     0x10001a235 addObject:
     0x10001a240 command
     0x10001a248 setRequiresDefaultDaemon:
     0x10001a262 setSaveInCache:
     0x10001a272 setSaveInCacheValueSet:
     0x10001a28a setUseCache:
     0x10001a297 setUseCacheValueSet:
     0x10001a2ac setGenerateIfNoCache:
     0x10001a2c2 setGenerateIfNoCacheValueSet:
     0x10001a2e0 setFastCacheTest:
     0x10001a2f2 setLowQuality:
     0x10001a301 setShowRects:
     0x10001a30f setQueueInvalidationTimeOut:
     0x10001a32c setQueueCancelTimeOut:
     0x10001a343 setMaxConcurrentRequestsCount:
     0x10001a362 setThumbnailSize:
     0x10001a374 setWantsIcon:
     0x10001a382 setWantsMask:
     0x100019e80 setScaleFactor:
     0x10001a390 setCompareWith1x:
     0x10001a3a2 setGenerateAllSizes:
     0x10001a3b7 setCompareWithLeopard:
     0x10001a3ce setCompareWithGeneric:
     0x10001a3e5 setSaveInAdditions:
     0x10001a3f9 setUseAdditions:
     0x10001a40a _parse_arguments_argc:argv:
     0x10001a426 arguments
     0x10001a430 count
     0x10001a436 setUseDaemon:
     0x10001a444 setGenerateCacheFile:
     0x10001a45a setWantsPerformanceInfo:
     0x10001a473 setCommand:
     0x10001a47f _parse_simple_command_argc:argv:
     0x10001a4a0 _parse_t_argc:argv:
     0x10001a4b4 _parse_p_argc:argv:
     0x10001a4c8 _parse_S_argc:argv:
     0x10001a4dc _parse_G_argc:argv:
     0x10001a4f0 resetNames
     0x10001a4fb statisticNames
     0x10001a50a countByEnumeratingWithState:objects:count:
     0x10001a535 componentsSeparatedByString:
     0x10001a552 objectAtIndex:
     0x10001a561 longLongValue
     0x10001a56f stringWithFormat:
     0x10001a581 URLWithString:
     0x10001a590 filePathURL
     0x10001a59c path
     0x10001a5a1 setIsSimpleRunCommand:
     0x10001a5b8 thumbnailSize
     0x100019e74 scaleFactor
     0x10001a5c6 forcedGeneratorPath
     0x10001a5da forceWindowServer
     0x10001a5ec wantsPerformanceInfo
     0x10001a601 outputFolder
     0x10001a60e setNeedsApplication:
     0x10001a623 _validateResetName:
     0x10001a637 validateResetName:
     0x10001a64a validateStatisticName:
     0x100019f5a isEqual:
     0x10001a661 fileExistsAtPath:
     0x10001a673 requiresDefaultDaemon
     0x10001a689 serverName
     0x10001a694 useDaemon
     0x10001a69e generateAllSizes
     0x10001a6af needsApplication
     0x10001a6c0 sharedApplication
     0x10001a6d2 usingURLs
     0x10001a6dc stringByStandardizingPath
     0x10001a6f6 fileURLWithPath:
     0x10001a707 useFileRefs
     0x10001a713 fileReferenceURL
     0x10001a724 _fileURLWithPath:
     0x10001a736 recursive
     0x10001a740 getResourceValue:forKey:error:
     0x10001a75f localizedDescription
     0x10001a774 boolValue
     0x10001a77e waitForDTrace
     0x10001a78c serverPort
     0x10001a797 displayUsage
     0x10001a7a4 drain
     0x10001a7aa displayLongUsage
     0x10001a7bb bundleWithPath:
     0x10001a7cb objectForInfoDictionaryKey:
     0x10001a7e7 _resetThumbnailsAgent:
     0x10001a7fe mutableCopy
     0x10001a80a removeObjectsInArray:
     0x10001a820 string
     0x10001a827 allKeys
     0x10001a82f compare:
     0x10001a838 sortedArrayUsingSelector:
     0x10001a852 lastObject
     0x10001a85d objectForKey:
     0x10001a86b appendFormat:
     0x10001a879 displayDiagnostic
     0x10001a88b _parsedURLsWithPath:
     0x10001a8a0 addObjectsFromArray:
     0x100019f45 sharedMessageHandler
     0x10001a0b1 setTestUtility:
     0x10001a8b5 setupAutoQuit
     0x10001a8c3 dictionary
     0x10001a8ce wantsIcon
     0x10001a8d8 setObject:forKey:
     0x10001a8ea numberWithFloat:
     0x10001a8fb saveInCacheValueSet
     0x10001a90f saveInCache
     0x10001a91b useCacheValueSet
     0x10001a92c useCache
     0x10001a935 useAdditions
     0x10001a942 generateIfNoCacheValueSet
     0x10001a95c generateIfNoCache
     0x10001a96e fastCacheTest
     0x10001a97c lowQuality
     0x10001a987 setValue:forKey:
     0x10001a998 setForcedContentType:
     0x10001a9ae removeObjectForKey:
     0x10001a9c2 computeThumbnails:
     0x10001a9d5 queueInvalidationTimeOut
     0x10001a9ee invalidateQueue
     0x10001a9fe performSelector:withObject:afterDelay:
     0x10001aa25 queueCancelTimeOut
     0x10001aa38 cancelQueue
     0x10001aa44 fileURLWithPath:isDirectory:
     0x10001aa61 prefersAutoPagination
     0x10001aa77 dictionaryWithObjects:forKeys:count:
     0x10001aa9c initWithURL:options:
     0x10001aab1 setForcedContentTypeWithType:
     0x10001aacf computePreviews:
     0x10001aae0 sharedPreviewPanel
     0x10001aaf3 defaultCenter
     0x10001ab01 previewPanelDidClose:
     0x10001ab17 addObserver:selector:name:object:
     0x10001ab39 setMandatoryServer:
     0x10001ab4d setDefaultOpenCloseEffect:
     0x10001ab68 setDelegate:
     0x10001ab75 activateIgnoringOtherApps:
     0x10001ab90 makeKeyAndOrderFront:
     0x10001aba6 run
     0x10001abaa currentRunLoop
     0x10001abb9 waitForLeaks
     0x10001abc6 _waitForLeaks
     0x10001abd4 arrayWithObject:
     0x10001abe5 terminate:
     0x10001abf0 containsObject:
     0x10001ac00 reset
     0x10001ac06 setDataSource:
     0x10001ac15 setShowsAddToiPhotoButton:
     0x10001ac30 setShowsFullscreenButton:
     0x10001ac4a modifierFlags
     0x10001ac58 charactersIgnoringModifiers
     0x10001ac74 isEqualToString:
     0x10001ac85 close
     0x10001b9c0 setShowThreads:
     0x10001b9d0 setWaitForLeaks:
     0x10001b9a2 setWaitForDTrace:
     0x10001ba3a setUseFileRefs:
     0x10001ba71 setForceWindowServer:
     0x10001bb01 stringWithCString:encoding:
     0x10001ba2c setRecursive:
     0x10001baa2 setNoFixup:
     0x10001baae setUsingURLs:
     0x10001ba06 compareWithLeopard
     0x10001ba19 compareWithGeneric
     0x10001b9eb maxConcurrentRequestsCount
     0x10001ba9a noFixup
     0x10001b933 terminate
     0x10001bb1d autoQuit:
     0x10001bb27 scheduledTimerWithTimeInterval:target:selector:userInfo:repeats:
     0x10001bb68 object
     0x10001bb6f windowController
     0x10001bb80 removeObject:
     0x10001bb8e terminateIfNecessary
     0x10001bba3 computeAllSizesForThumbnails:
     0x10001bbc1 detachNewThreadSelector:toTarget:withObject:
     0x10001bbee copy
     0x10001bbf3 previewsThread
     0x10001bc02 performSelectorInBackground:withObject:
     0x10001bc2a thumbnailDidFinish:
     0x10001bc3e performSelectorOnMainThread:withObject:waitUntilDone:
     0x10001bc74 absoluteString
     0x10001b8db printDot:
     0x10001bc83 lastPathComponent
     0x10001bc95 stringByAppendingString:
     0x10001b9e1 wantsMask
     0x10001bcae copyImageMask
     0x10001bcbc stringByAppendingPathComponent:
     0x10001bcdc stringByAppendingPathExtension:
     0x10001bcfc initWithWindowNibName:owner:
     0x10001bd19 window
     0x100019e2c setCgImage:
     0x100019e44 setContentRect:
     0x100019e62 setRequestedSize:
     0x100019e90 setBaselineOffsetFromBottom:
     0x10001bd20 setWindow:
     0x10001bd2b setRepresentedFilename:
     0x10001bd43 colorWithCalibratedWhite:alpha:
     0x10001bd63 setBackgroundColor:
     0x10001bd77 displayNameAtPath:
     0x10001bd8a setTitle:
     0x10001bd94 thumbnailWindowDidClose:
     0x10001bdad setImage:
     0x10001bdb7 generationQueue
     0x10001bdc7 generateLocallyWithQueue:completion:
     0x10001bdec stringByDeletingLastPathComponent
     0x10001be0e pathExtension
     0x10001be1c length
     0x10001be23 writeToFile:options:error:
     0x10001a05a debugDescription
     0x10001be3e writeToFile:atomically:
     0x10001be56 URLByAppendingPathComponent:
     0x10001be73 dataWithContentsOfURL:options:error:
     0x10001be98 propertyListWithData:options:format:error:
     0x10001bec3 enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:
     0x10001bf04 initWithData:encoding:
     0x10001bf1b keyEnumerator
     0x10001bf29 stringByReplacingOccurrencesOfString:withString:
     0x10001bf5a dataUsingEncoding:
     0x10001bf6d writeToURL:options:error:
     0x10001bf87 _getNextData:completion:
     0x10001bfa0 getNextData:
     0x10001bfad url
     0x10001bfb1 retrievePreviewURL
     0x10001bfc4 getProperties
     0x10001bfd2 synchronousGetData
     0x10001bfe5 isRawImage
     0x10001bff0 retrievePreviewContentType
     0x10001c00b createDirectoryAtPath:withIntermediateDirectories:attributes:error:
     0x10001c04f _dumpPreviewProperties:atPath:withAttachmentIndex:
     0x10001c082 stringByDeletingPathExtension
     0x10001c0a0 _fixQLPreviewAtURL:
     0x10001c0b4 previewDidFinish:
     0x10001c0c6 retrieveDisplayBundleIDForAdvancedUsage:
     0x10001c0ef previewDone:
     0x10001c0fc thumbnailQueue:didFinish:
     0x10001c21c graphicsContextWithGraphicsPort:flipped:
     0x10001c245 systemFontOfSize:
     0x10001c257 dictionaryWithObject:forKey:
     0x10001c274 saveGraphicsState
     0x10001c286 setCurrentContext:
     0x10001c299 sizeWithAttributes:
     0x10001c2ad drawInRect:withAttributes:
     0x10001c2c8 restoreGraphicsState
     0x10001c2dd copyIconImageFromURL:size:scale:darkMode:
     0x10001c307 discardPreviewRequest:
     0x10001c31e queuePreviewRequest:
     0x10001c333 setupCrashReportMessageForRequest:
     0x10001c356 processInfo
     0x10001c362 activeProcessorCount
     0x10001b8e5 parseArgc:argv:
     0x10001b8f5 prepare
     0x10001b8fd displayCommand
     0x10001ba87 isSimpleRunCommand
     0x10001c377 fileSystemRepresentation
     0x10001c390 initWithTitle:
     0x10001c39f addItem:
     0x10001c3a8 initWithTitle:action:keyEquivalent:
     0x10001c3cc setSubmenu:
     0x10001c3d8 setMainMenu:
     0x10001c3e5 setActivationPolicy:
     0x10001c3fa initWithContentsOfFile:
     0x10001c412 setApplicationIconImage:
     0x10001c42b initWithMachPort:supportsTransaction:
     0x10001c451 forceGenerator:andContentTypeUTI:
     0x10001c473 checkForLastModDateForQuickLookLibraries
     0x10001c49c detachServerThread
     0x10001ba62 setServerPort:
     0x10001c4b7 date
     0x10001c532 disableInstantOff
     0x10001c544 enableInstantOff
     0x10001c555 sharedController
     0x10001c566 clearAllRequests
     0x10001c577 exitImmediately
     0x10001c587 _updateLastModDateForQuickLookLibraries
     0x10001c5af _storeLastModDateForQuickLookLibraries
     0x10001c5d6 discardAllRequestsWithNoRetry:
     0x10001c5f5 _exit
     0x10001c5fb stopServerThreadSoon
     0x10001c610 standardUserDefaults
     0x10001c625 prepareToExit
     0x10001c633 serverIsIdle
     0x10001c640 serverIsWorking
     0x10001c650 _deadRequestPortNotification:
     0x10001c66e setupSessions:deadPortBlock:
     0x10001c68b setMaxConcurrentOperationCount:
     0x10001c6ab initWithObjects:
     0x10001c6bc _updateLocale
     0x10001c6ca addObserverForName:object:queue:usingBlock:
     0x10001c6f6 hasPrefix:
     0x10001c701 stringByExpandingTildeInPath
     0x10001c71e _defaultsKeyForQuickLookLibrary:
     0x10001c73f initWithFormat:
     0x10001c74f _lastModDateForQuickLookLibrary:
     0x10001c770 numberWithUnsignedInteger:
     0x10001c78b unsignedIntegerValue
     0x10001c7a0 _setupKQueueForGeneratorChanges
     0x10001c7c0 serverWork
     0x10001c7cb sessionCount
     0x10001c7d8 isIdle
     0x10001c7df discardAllSessions:
     0x10001c7f3 perform:
     0x10001c4c4 setRequest:
     0x10001c4e0 setTimeOutInterval:
     0x10001c504 setExecDescription:
     0x10001c7fc _untrustedCodeTimeOut:
     0x10001c51e setTimer:
     0x10001c518 timer
     0x10001c813 invalidate
     0x10001c4bc request
     0x10001c4f4 execDescription
     0x10001c81e fireDate
     0x10001c827 dateWithTimeIntervalSinceNow:
     0x10001c845 earlierDate:
     0x10001c852 setFireDate:
     0x10001c85f userInfo
     0x10001c528 startDate
     0x10001c868 _startUntrustedCodeForRequest:withTimeOut:description:
     0x10001c89f _stopUntrustedCodeForRequest:
     0x10001c8bd _checkMemoryUsage
     0x10001c8cf cancelPreviousPerformRequestsWithTarget:selector:object:
     0x10001c908 _scheduleMemoryUsageCheck
     0x10001c922 _useSatelliteForRequest:
     0x10001c93b satelliteForRequest:
     0x10001c950 cancelRequest:
     0x10001c95f _makeSureRequest:hasBeenFinishedIn:reason:
     0x10001c98a getSessionAndNotifyPortDeathWithPort:
     0x10001c9b0 _stopRequest:
     0x10001c9be _updateIdle
     0x10001c9ca unsetupSession:
     0x10001c9da enqueueRequest:completionBlock:
     0x10001c9fa setupSession:
     0x10001ca08 _updateNoIdle
     0x10001ca16 updateLastHitDateOfAddition:onPhysicalURL:
     0x10001ca41 initWithAdditionsPresentOnURL:error:
     0x10001ca66 thumbnailWithMaximumDimension:contentRect:flavor:lowQuality:properties:
     0x10001caae numberWithInt:
     0x10001cabd touchOrAddThumbnailAddition:forURL:
     0x10001cae1 getPromisedItemResourceValue:forKey:error:
     0x10001cb0c _dispatchPreviewRequest:
     0x10001cb25 _queueRequest:fallbackBlock:
     0x10001cb42 set
     0x10001cb46 isInstantOffEnabled
     0x10001cb5a appendString:
     0x10001cb68 _addStatIfUsefulFor_disks:
     0x10001cb83 _addStatFor_server:
     0x10001cb97 _addStatFor_memory:
     0x10001cbab _addStatFor_burst:
     0x10001cbbe _addStatFor_other:
     0x10001cbd1 bundleWithIdentifier:
     0x10001cbe7 bundlePath
     0x10001cbf2 arrayWithObjects:
     0x100019f7f performSelector:withObject:
     0x10001cc04 hasSuffix:
     0x10001cc0f substringWithRange:
     0x10001cc23 sortUsingComparator:
     0x10001cc38 _namesForPrefix:withParameter:
     0x10001cc57 instancesRespondToSelector:
     0x10001cc73 stopServerThreadWhenIdle
     0x10001cc8c removeAllAdditions
     0x10001cc9f askThumbnailAdditionIndex:
     0x10001ccf5 _librariesHaveChanged:
     0x10001cd0c _lsDatabaseHasChanged
     0x10001ccba _stopFromKill

 */