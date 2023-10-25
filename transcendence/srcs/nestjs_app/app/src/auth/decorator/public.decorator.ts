import { SetMetadata } from "@nestjs/common";

// This custom decorator send the Metadata decorator so that we know
// this route is public
// It is basicaly a function that returns the call to SetMetadata
export const Public = () => SetMetadata('isPublic', true)