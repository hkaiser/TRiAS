unit LTTMBOCX;
interface

const

{$I LEADLock.pas}

   {ThumbnailBrowseStatusConstants}
   BROWSE_LOADING = 2; { used to indicate image is being loaded }
   BROWSE_SKIPPED = 3; { used to indicate image was skipped b/c it was larger than the specified range }
   BROWSE_PRELOAD = 4; { used to indicate image is about to be loaded }

implementation
end.
