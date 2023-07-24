import { IsEmpty, IsEnum, IsNotEmpty, IsOptional, IsString } from "class-validator";
import { UserStatus } from "../user-status.enum";

export class GetFriendsFilterDto
{   
    @IsOptional()
    @IsEnum(UserStatus)
    status?: UserStatus;
}