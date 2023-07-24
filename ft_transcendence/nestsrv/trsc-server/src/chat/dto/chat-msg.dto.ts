import { ApiProperty } from "@nestjs/swagger";
import { IsString } from "class-validator";

export class ChatMsgDto {
    @ApiProperty()
    @IsString()
    from: string;

    @ApiProperty()
    @IsString()
    to: string;

    @ApiProperty()
    @IsString()
    body: string;
}